#ifndef AOC_RANGE_HPP
#define AOC_RANGE_HPP

#include <iostream>

template<typename T>
struct range
{
    range(T min, T max)
        : min_{ min }
        , max_{ max }
    {}

    [[nodiscard]] auto min() const -> T { return min_; }
    [[nodiscard]] auto max() const -> T { return max_; }
    [[nodiscard]] auto contains(T x) const -> bool
    {
        return min_ <= x && x <= max_;
    }

    auto operator<=>(const range&) const = default;

  private:
    T min_;
    T max_;
};

template<typename T>
auto operator<<(std::ostream& out, const range<T>& range) -> std::ostream&
{
    return out << "range { " << range.min() << ", " << range.max() << " }";
}

#endif
