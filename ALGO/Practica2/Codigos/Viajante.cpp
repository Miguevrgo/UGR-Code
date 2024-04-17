#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>
#include <limits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

int UMBRAL = 4; // Threshold to apply brute force 

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}

    /**
     * @brief Calculates the distance between two points using the 
     * Euclidean distance formula.
     * 
     * @param p other point
     * @return Distance between the two points
     */
    double distanceTo(const Point &p) const {
        return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << "" << point.x << "," << point.y << "";
        return os;
    }

private:
    int x, y;
};


/**
 * @brief This function calculates the minimum distance required to visit
 * all the points in the vector once, to do so, it generates all the possible
 * permutations of the vector and calculates the distance needed to visit all
 * the points in the order of the permutation.
 * 
 * @note Distance from first to last point has to be calculated to make a closed path.
 * @note iota generates a sequence of numbers from 0 to n.
 * @note If needed, it can return the permutation that generates the minimum distance.
 * 
 * @param points which will be used to calculate the minimum distance
 * @return minimum distance to visit all the points
 */
vector<Point> bruteForceTSP(const std::vector<Point>& points) {
    std::vector<int> permutation(points.size());
    std::iota(permutation.begin(), permutation.end(), 0);

    double minDistance = std::numeric_limits<double>::max();
    std::vector<int> bestPermutation;
    do {
        double distance = 0;
        for (int i = 0; i < permutation.size() - 1; ++i) {
            distance += points[permutation[i]].distanceTo(points[permutation[i + 1]]);
        }

        distance += points[permutation.back()].distanceTo(points[permutation.front()]);
        if (distance < minDistance) {
            minDistance = distance;
            bestPermutation = permutation;
        }
    } while (std::next_permutation(permutation.begin(), permutation.end()));

    std::vector<Point> bestPath;
    for (int index : bestPermutation) {
        bestPath.emplace_back(points[index]);
    }

    return bestPath;
}


/**
 * @brief This function calculates the distance of a given closed path.
 * 
 * @param points to visit
 * @return total distance to visit all the points
 */
double totalDistance(const vector<Point>& points) {
  double distance = 0;
  for (int i = 0; i < points.size() - 1; ++i) {
    distance += points[i].distanceTo(points[i + 1]);
  }
  distance += points.back().distanceTo(points.front());
  return distance;
}


/**
 * @brief This function optimizes a given tour by swwapping pairs of points
 * until the tour can't be improved anymore by swapping points.
 * 
 * @param tour  to optimize
 * @return optimized tour
 */
std::vector<Point> optimizeTour(const std::vector<Point>& tour) {
    std::vector<Point> currentTour = tour;
    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (int i = 1; i < currentTour.size() - 2; ++i) {
            for (int j = i + 2; j < currentTour.size(); ++j) {

                double originalDistance = currentTour[i - 1].distanceTo(currentTour[i]) +
                                          currentTour[j - 1].distanceTo(currentTour[j]);
                double swappedDistance = currentTour[i - 1].distanceTo(currentTour[j - 1]) +
                                         currentTour[i].distanceTo(currentTour[j]);

                if (swappedDistance < originalDistance) {
                    std::reverse(currentTour.begin() + i, currentTour.begin() + j);
                    improvement = true;
                }
            }
        }
    }

    return currentTour;
}


/**
 * @brief Calculates an approximate distance travelled with lower precision
 * but higher speed compared to best distance using the divide and conquer
 * approach.
 * 
 * @note The function uses global variable UMBRAL to determine when to use
 * brute force instead of divide and conquer. UMBRAL is set to 8 by default.
 * where it offers the best performance.
 * 
 * @param points 
 * @return std::vector<Point> 
 */
std::vector<Point> divideAndConquerTSP(const std::vector<Point>& points) {
    if (points.size() <= UMBRAL) {
        return bruteForceTSP(points);
    }

    int mid = points.size() / 2;
    std::vector<Point> left(points.begin(), points.begin() + mid);
    std::vector<Point> right(points.begin() + mid, points.end());

    std::vector<Point> leftTour = divideAndConquerTSP(left);
    std::vector<Point> rightTour = divideAndConquerTSP(right);

    std::vector<Point> combinedTour = leftTour;
    combinedTour.insert(combinedTour.end(), rightTour.begin(), rightTour.end());


    return optimizeTour(combinedTour);
}





int main(int argc, char* argv[]) {

    if (strcmp(argv[2],"1") == 0) { // Random or Graph Results
        const int VEC_SIZE = atoi(argv[1]);
        vector<Point> randomPoints;
        randomPoints.reserve(VEC_SIZE);
        vector<Point> approximatePath; 
        approximatePath.reserve(VEC_SIZE);
        srand(time(NULL));

        for (int i = 0; i < VEC_SIZE; ++i) {
            int x = rand() % 100 - 50;
            int y = rand() % 100 - 50;
            randomPoints.emplace_back(Point(x, y));
            approximatePath.emplace_back(Point(x, y));
        }

        // /*------------------------|Para graficar los grafos|------------------*/
        // std::ofstream outputFile("tsp_results.csv");
        // divideAndConquerTSP(approximatePath);

        // outputFile << std::endl;
        // for (const Point& point : approximatePath) {
        //     outputFile << point.getX() << "," << point.getY() << std::endl;
        // }
        // //-----------------------|Fin graficar resultados|---------------------*/
        
        //std::cout << "Brute Force: " << totalDistance(bruteForceTSP(randomPoints)) << std::endl;
        // std::cout <<totalDistance(divideAndConquerTSP(approximatePath)) << std::endl;
    } 
    else if (strcmp(argv[2],"2") == 0){ // Get the distance of Cities
        std::string file = argv[1];
        std::ifstream input(file);
        std::vector<Point> points;
        double x, y;
        int size;
        int pos;
        input >> size;
        points.reserve(size);
        for (int i = 0; i < size; ++i) {
            input >> pos >> x >> y;
            points.emplace_back(Point(x, y));
        }
        input.close();
        std::cout << std::fixed;
        std::cout.precision(2);
        std::cout << file << ": " << totalDistance(divideAndConquerTSP(points)) << std::endl;

    }
    else { // Calculate time
        const int VEC_SIZE = atoi(argv[1]);
        vector<Point> randomPoints;
        randomPoints.reserve(VEC_SIZE);
        srand(time(NULL));

        for (int i = 0; i < VEC_SIZE; ++i) {
            int x = rand() % 100 - 50;
            int y = rand() % 100 - 50;
            randomPoints.emplace_back(Point(x, y));
        }
        std::cout << std::fixed;
        std::cout.precision(6);
        std::cout << VEC_SIZE << " ";
        //Time measurement
        std::chrono::duration<double> elapsed;
        auto start = std::chrono::high_resolution_clock::now();
        divideAndConquerTSP(randomPoints);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        std::cout << elapsed.count() << "\n";
    }


    return 0;
}