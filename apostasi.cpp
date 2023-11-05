
#include <iostream>
#include <cmath>

struct Shmeio {
    double x, y;
};

double efklapost(const Shmeio& p1, const Shmeio& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}