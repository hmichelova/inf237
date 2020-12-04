#include <iostream>
#include <vector>
#include <algorithm>

class Layout {
public:
    Layout(int w, int h, int x, int y, int id) 
        : w(w), h(h), x(x), y(y), id(id) {
        area = w * h;    
    }

    static bool isOut(int xa1, int ya1, int xa2, int ya2
                    , int xb1, int yb1, int xb2, int yb2) {
        return xa2 <= xb1 || xa1 >= xb2 || ya2 <= yb1 || ya1 >= yb2;
    }

    long long addLayout(int w1, int h1, int x1, int y1, int id1) {
        if (isOut(x, y, x + w, y + h, x1, y1, x1 + w1, y1 + h1)) {
            return 0;
        }

        overlap |= (1 << id1);
        return (1 << id);
    }

    void addLayout(long long add) {
        overlap |= add;
    }

    long long getArea() const {
        return area;
    }

    long long getOverlap() const {
        return overlap;
    }

private:
    int w, h, x, y, id;
    long long overlap = 0;
    long long area = 0;

};

long long result = 0;

void calculate(int n, const std::vector<Layout> &layouts, int id, long long used, long long area) {
    if (id >= n) {
        result = std::max(result, area);
        return;
    }

    if ((layouts.at(id).getOverlap() & used) == 0) {
        calculate(n, layouts, id + 1, used | (1 << id), area + layouts.at(id).getArea());
    }

    calculate(n, layouts, id + 1, used, area);
}

int main(void) {
    while (true) {
        result = 0;
        int n;
        std::cin >> n;

        if (n == 0) {
            return 0;
        }

        int w, h, x, y;
        std::vector<Layout> layouts;
        for (int j = 0; j < n; j++) {
            std::cin >> w >> h >> x >> y;
            Layout l(w, h, x, y, j);
            for (auto &oldL : layouts) {
                long long toAdd = oldL.addLayout(w, h, x, y, j);
                l.addLayout(toAdd);
            }

            layouts.push_back(l);
        }

        calculate(n, layouts, 0, 0, 0);
        std::cout << result << std::endl;
    }

    return 0;
}

