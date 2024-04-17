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
 * @brief This function optimizes a given tour by swwapping pairs of points
 * until the tour can't be improved anymore by swapping points. (2-Opt technique)
 * 
 * @param tour  to optimize
 * @return optimized tour
 */
void improve2Opt(std::vector<Point>& path) {
    bool improvement = true;
    while (improvement) {
        improvement = false;
        int n = path.size();
        for (int i = 0; i <= n - 2; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double oldDistance = path[i].distanceTo(path[(i + 1) % n]) + path[j].distanceTo(path[(j + 1) % n]);
                double newDistance = path[i].distanceTo(path[j]) + path[(i + 1) % n].distanceTo(path[(j + 1) % n]);
                if (newDistance < oldDistance) {
                    std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }
}


// Function to implement a single 3-opt swap
void improveTourWith3Opt(std::vector<Point>& tour) {
    bool improvementMade = true;
    while (improvementMade){
        improvementMade = false;
        const size_t n = tour.size();

        for (size_t i = 1; i < n - 3; ++i) {
            for (size_t j = i + 2; j < n - 1; ++j) {
                double distBefore = tour[i - 1].distanceTo(tour[i]) + tour[i].distanceTo(tour[j]) + tour[j].distanceTo(tour[j + 1]);
                double distAfter = tour[i - 1].distanceTo(tour[j]) + tour[j].distanceTo(tour[i]) + tour[i].distanceTo(tour[j + 1]);

                if (distBefore > distAfter) {
                    std::reverse(tour.begin() + i, tour.begin() + j + 1);
                    improvementMade = true;
                }
            }
        }
    }
}
