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

    bool operator<(const Point &p) const {
        if (x == p.x){
            return y < p.y;
        }
        else{
            return x < p.x;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "" << point.x << "," << point.y << "";
        return os;
    }

private:
    int x, y;
};


/**
 * @brief Greedy algorithm that approximates the shortest path to visit all the 
 * points in a given tour. The metodology is to sort the points by their 
 * x and y coordinates 
 * 
 * @note That we really are sorting the points by their x coordinates if 
 * the difference between the x coordinates is less than 10, otherwise we
 * sort by the y coordinates. (This is to prevent from going up and down 
 * large distances when not necessary)
 * 
 * @param points 
 * @return std::vector<Point> 
 */
std::vector<Point> CircTSP(const std::vector<Point>& points) {
    std::vector<Point> tour;
    std::vector<Point> circularTour;
    tour.reserve(points.size());
    circularTour.reserve(points.size());
    tour = points;
    std::sort(tour.begin(), tour.end());
    
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();

    for (int i = 0; i < points.size(); ++i) {
        min = std::min(min, points[i].getY());
        max = std::max(max, points[i].getY());
    }
    
    double mid = (max + min )/2;

    for (int i = 0; i < points.size(); ++i) {
        if (tour[i].getY() <= mid) {
            circularTour.emplace_back(tour[i]);
        }
    }

    for (int i = points.size(); i >= 0; --i) {
        if (tour[i].getY() > mid) {
            circularTour.emplace_back(tour[i]);
        }
    }

    improve2Opt(circularTour);
    return circularTour;
}

/**
 * @brief This function calculates the distance of a given closed path.
 * 
 * @param points to visit
 * @return total distance to visit all the points
 */
double totalDistance(const std::vector<Point>& points) {
    double distance = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        distance += points[i].distanceTo(points[i + 1]);
    }
    distance += points.back().distanceTo(points.front());
    return distance;
}



int main(int argc, char* argv[]) {
    if (strcmp(argv[2],"1") == 0) { // Random or Graph Results
        const int VEC_SIZE = atoi(argv[1]);
        std::vector<Point> approximatePath; 
        std::vector<Point> path;
        approximatePath.reserve(VEC_SIZE);
        path.reserve(VEC_SIZE);
        
        srand(time(NULL));

        for (int i = 0; i < VEC_SIZE; ++i) {
            int x = rand() % 100 - 50;
            int y = rand() % 100 - 50;
            approximatePath.emplace_back(Point(x, y));
            path.emplace_back(Point(x, y));
        }

        /*------------------------|Para graficar los grafos|------------------*/
        std::ofstream outputFile("tsp_results.csv");
        path = CircTSP(approximatePath);

        outputFile << std::endl;
        for (const Point& point : path) {
            outputFile << point.getX() << "," << point.getY() << std::endl;
        }

        //-----------------------|Fin graficar resultados|---------------------*/
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
        std::cout << size << " " << totalDistance(CircTSP(points)) << std::endl;
    }



    return 0;
}