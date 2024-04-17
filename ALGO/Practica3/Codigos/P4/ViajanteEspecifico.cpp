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

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
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
std::vector<Point> bruteForceTSP(const std::vector<Point>& points) {
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