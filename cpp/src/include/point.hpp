#ifndef AOC_POINT_HPP
#define AOC_POINT_HPP

#include <iostream>

template<typename T>
struct point
{
    point(T x_, T y_)
        : x{ x_ }
        , y{ y_ }
    {}

    auto operator<=>(const point&) const = default;

    T x;
    T y;
};

template<typename T>
auto operator<<(std::ostream& out, const point<T>& point) -> std::ostream&
{
    return out << "point { " << point.x << ", " << point.y << " }";
}

#endif
