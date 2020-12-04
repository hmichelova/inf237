#include <iostream>
#include <vector>
#include <algorithm>

class Point {
public: 
    Point(long long i, long long x, long long y) : x(x), y(y), index(i) {}

    long long getX() const {
        return x;
    }

    long long getY() const {
        return y;
    }

    long long getIndex() const {
        return index;
    }
    
private:
    long long x, y, index;
};

bool isCorrectTurn(const Point &p1, const Point &p2, const Point &p3) {
    return (p2.getY() - p1.getY()) * (p3.getX() - p2.getX()) - 
      (p2.getX() - p1.getX()) * (p3.getY() - p2.getY()) > 0;
}

void calculate(std::vector<Point> &points, int n) {
    std::vector<Point> polygon;
    int count = 2;
    std::vector<bool> isInStack(n, false);

    polygon.push_back(points.at(0));
    polygon.push_back(points.at(1));
    isInStack[points[0].getIndex()] = true;
    isInStack[points[1].getIndex()] = true;

    for (int i = 2; i < n; i++) {
        if (isCorrectTurn(polygon.at(count - 2), polygon.at(count - 1), points.at(i))) {
            isInStack[polygon.back().getIndex()] = false;
            polygon.pop_back();
            while (count > 2 && isCorrectTurn(polygon.at(count - 3), polygon.at(count - 2), points.at(i))) {
                count--;
                isInStack[polygon.back().getIndex()] = false;
                polygon.pop_back();
            }
        } else {
            count++;
        }

        isInStack[points[i].getIndex()] = true;
        polygon.push_back(points.at(i));
    }

    for (int i = n - 1; i >= 0; i--) {
        if (!isInStack[points.at(i).getIndex()]) {
            polygon.push_back(points.at(i));
        }
    }

    std::string sep = "";
    for (Point &p : polygon) {
        std::cout << sep << p.getIndex();
        sep = " ";
    }
    std::cout << std::endl;
}

int main(void) {
    int n;
    std::cin >> n;
    for (int test = 0; test < n; test++) {
        long long curr;
        std::cin >> curr;
        std::vector<Point> points;
        for (int i = 0; i < curr; i++) {
            long long x, y;
            std::cin >> x >> y;
            points.push_back(Point(i, x, y));
        }

        std::sort(points.begin(), points.end(), [&](const Point &p1, const Point &p2) 
          { return p1.getY() == p2.getY() ? p1.getX() < p2.getX() : p1.getY() < p2.getY(); });
        
        calculate(points, curr);
    }
    
    return 0;
}

