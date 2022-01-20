#ifndef AOC_PRINT_HPP
#define AOC_PRINT_HPP

#include <array>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

template<typename T>
auto operator<<(std::ostream& out, const std::vector<T>& vec) -> std::ostream&
{
    out << "[ ";
    for (const auto& e : vec) {
        out << e << ", ";
    }
    return out << " ]";
}

template<typename T, typename V>
auto operator<<(std::ostream& out, const std::pair<T, V>& pair) -> std::ostream&
{
    return out << "{ " << pair.first << ", " << pair.second << "}";
}

template<typename T>
auto operator<<(std::ostream& out, const std::set<T>& set) -> std::ostream&
{
    out << "[ ";
    for (const auto& e : set) {
        out << e << ", ";
    }
    return out << " ]";
}

template<typename T, std::size_t n>
auto operator<<(std::ostream& out, const std::array<T, n>& arr) -> std::ostream&
{
    out << "[ ";
    for (const auto& a : arr) {
        out << a << ", ";
    }
    return out << "]";
}

#endif