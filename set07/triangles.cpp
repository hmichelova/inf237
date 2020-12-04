#include <iostream>
#include <vector>

class Line {
public:
    Line(double x1, double y1, double x2, double y2) 
        : x1(x1), y1(y1), x2(x2), y2(y2) {
        x = x1 - x2;
        y = y1 - y2;
    }

    static bool isParalell(const Line &l1, const Line &l2) {
        return l1.x * l2.y == l1.y * l2.x;
    }

    static bool hasIntersection(const Line &l1, const Line&l2) {
        if (Line::isParalell(l1, l2)) {
            return false;
        }

        double t11 = (l2.y1 - l2.y2) * (l1.x1 - l2.x1) + (l2.x2 - l2.x1) * (l1.y1 - l2.y1);
        double t12 = (l2.x2 - l2.x1) * (l1.y1 - l1.y2) - (l1.x1 - l1.x2) * (l2.y2 - l2.y1);
        double t21 = (l1.y1 - l1.y2) * (l1.x1 - l2.x1) + (l1.x2 - l1.x1) * (l1.y1 - l2.y1);
        double t22 = (l2.x2 - l2.x1) * (l1.y1 - l1.y2) - (l1.x1 - l1.x2) * (l2.y2 - l2.y1);

        return t12 != 0 && t22 != 0 && 0 <= t11 / t12 && t11 / t12 <= 1 
            && 0 <= t21 / t22 && t21 / t22 <= 1;
    }

    bool addLine(const Line &line, int id) {
        if (Line::hasIntersection(*this, line)) {
            idInter.push_back(id);
            return true;
        }

        return false;
    }

    void add(int id) {
        idInter.push_back(id);
    }

    long long countTriangles(const std::vector<std::vector<bool>> &inter) const {
        long long count = 0;
        for (int i = 0; i < idInter.size(); i++) {
            for (int j = i + 1; j < idInter.size(); j++) {
                if (inter.at(idInter.at(i)).at(idInter.at(j))) {
                    count++;
                }
            }
        }

        return count;
    }

    void print() const {
        for (int i : idInter) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    
private:
    std::vector<int> idInter;
    double x1, y1, x2, y2, x, y;
};

void newLine(std::vector<Line> &lines, std::vector<std::vector<bool>> &inter
    , double x1, double y1, double x2, double y2, int id) {
    Line line(x1, y1, x2, y2);
    std::vector<bool> lineInter;
    for (int i = 0; i < id; i++) {
        Line &l = lines[i];
        bool hasIntersection = l.addLine(line, id);
        if (hasIntersection) {
            line.add(i);
        }

        inter[i].push_back(hasIntersection);
        lineInter.push_back(hasIntersection);
    }

    lineInter.push_back(false);
    inter.push_back(lineInter);
    lines.push_back(line);
}

int main(void) {
    int n;
    std::cin >> n;

    while (n != 0) {
        double x1, y1, x2, y2;
        std::vector<Line> lines;
        std::vector<std::vector<bool>> inter;
        for (int i = 0; i < n; i++) {
            std::cin >> x1 >> y1 >> x2 >> y2;
            newLine(lines, inter, x1, y1, x2, y2, i);
        }

        long long countTriangles = 0;
        for (const auto &line : lines) {
            countTriangles += line.countTriangles(inter);
        }

        std::cout << countTriangles / 3 << std::endl;

        std::cin >> n;
    }
    
    return 0;
}

