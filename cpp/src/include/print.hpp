#ifndef AOC_PRINT_HPP
#define AOC_PRINT_HPP

#include <array>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <variant>
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

template<typename T>
auto operator<<(std::ostream& out, const std::list<T>& vec) -> std::ostream&
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

template<typename K, typename V>
auto operator<<(std::ostream& out, const std::map<K, V>& map) -> std::ostream&
{
    out << "{ ";
    for (const auto& p : map) {
        out << p << ", ";
    }
    return out << " }";
}

template<typename... Args>
auto operator<<(std::ostream& out, const std::variant<Args...>& variant)
    -> std::ostream&
{
    std::visit([&](const auto& x) { out << x; }, variant);
    return out;
}

#endif
