#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

class Point {
public: 
    Point(long long x, long long y) : x(x), y(y) {}

    long long getX() const {
        return x;
    }

    long long getY() const {
        return y;
    }

    void negate() {
        x = -x;
        y = -y;
    }

private:
    long long x, y;
};

double polygonArea(std::vector<Point> &points, int count) {
    double area = 0;

    for (int i = 0; i < count; i++) {
        int j = (i + 1) % count;
        area += 0.5 * (points[i].getX() * points[j].getY() - points[j].getX() * points[i].getY());
    }

    return area;
}

bool isCorrectTurn(const Point &p1, const Point &p2, const Point &p3) {
    return (p2.getY() - p1.getY()) * (p3.getX() - p2.getX()) - 
      (p2.getX() - p1.getX()) * (p3.getY() - p2.getY()) > 0;
}

double oneHalf(std::vector<Point> &points, int n) {
    std::vector<Point> polygon;
    int count = 2;

    polygon.push_back(points.at(0));
    polygon.push_back(points.at(1));

    for (int i = 2; i < n; i++) {
        if (isCorrectTurn(polygon.at(count - 2), polygon.at(count - 1), points.at(i))) {
            polygon.pop_back();
            while (count > 2 && isCorrectTurn(polygon.at(count - 3), polygon.at(count - 2), points.at(i))) {
                count--;
                polygon.pop_back();
            }
        } else {
            count++;
        }

        polygon.push_back(points.at(i));
    }

    return polygonArea(polygon, count);
}

double calculate(std::vector<Point> &points, int n) {
    double area = oneHalf(points, n);
    
    for (Point &p : points) {
        p.negate();
    }
    std::reverse(points.begin(), points.end());

    area += oneHalf(points, n);
    return area;
}

int main(void) {
    int n;
    std::cin >> n;
    while (n > 0) {
        std::vector<Point> points;
        for (int i = 0; i < n; i++) {
            long long x, y;
            std::cin >> x >> y;
            points.push_back(Point(x, y));
        }

        if (n == 1) {
            std::cout << 0 << std::endl;
            std::cin >> n;
            continue;
        }

        std::sort(points.begin(), points.end(), [&](const Point &p1, const Point &p2) 
          { return p1.getY() == p2.getY() ? p1.getX() < p2.getX() : p1.getY() < p2.getY(); });
        
        std::cout << calculate(points, n) << std::endl;
        std::cin >> n;
    }
    
    return 0;
}

