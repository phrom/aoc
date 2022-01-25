#ifndef AOC_ORDERED_VECTOR_HPP
#define AOC_ORDERED_VECTOR_HPP

#include <algorithm>

template<typename T, typename Comparison = std::less<T>>
struct ordered_vector
{
    ordered_vector() = default;

    explicit ordered_vector(const Comparison& comparison)
        : comparison_{ comparison }
    {}

    ordered_vector(ordered_vector&&) noexcept = default;

    void push(const T& value)
    {
        vector_.insert(
            std::lower_bound(
                vector_.begin(), vector_.end(), value, comparison_),
            value);
    }

    void erase(auto it) { vector_.erase(it); }

    [[nodiscard]] auto front() const { return vector_.front(); }
    [[nodiscard]] auto empty() const { return vector_.empty(); }
    [[nodiscard]] auto begin() const { return vector_.begin(); }
    [[nodiscard]] auto end() const { return vector_.end(); }
    [[nodiscard]] auto size() const { return vector_.size(); }

  private:
    std::vector<T> vector_{};
    Comparison comparison_{};
};
#endif
