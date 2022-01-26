#ifndef AOC_MATRIX_HPP
#define AOC_MATRIX_HPP

#include <iostream>
#include <vector>

template<typename T>
struct matrix
{
    matrix() = default;
    matrix(matrix&&) noexcept = default;

    [[nodiscard]] auto get(uint64_t i, uint64_t j) const -> T
    {
        return m_[i][j];
    }

    void set(uint64_t i, uint64_t j, const T& v)
    {
        ensure_size(i, j);
        m_[i][j] = v;
    }

    [[nodiscard]] auto rows() const -> uint64_t { return m_.size(); }

    [[nodiscard]] auto columns(uint64_t row) const -> uint64_t
    {
        return m_[row].size();
    }

    void remove_rows(uint64_t new_size) { m_.resize(new_size); }

    void remove_columns(uint64_t new_size)
    {
        for (auto& r : m_) {
            r.resize(new_size);
        }
    }

    void reserve(uint64_t rows, uint64_t columns)
    {
        m_.reserve(rows);
        for (auto& row : m_) {
            row.reserve(columns);
        }
    }

  private:
    void ensure_size(uint64_t i, uint64_t j)
    {
        if (i >= m_.size()) {
            m_.resize(i + 1);
        }
        if (j >= m_[i].size()) {
            m_[i].resize(j + 1);
        }
    }

    std::vector<std::vector<T>> m_;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& matrix)
{
    out << "[ ";
    for (int i = 0; i < matrix.rows(); ++i) {
        out << "\n[ ";
        for (int j = 0; j < matrix.columns(i); ++j) {
            out << matrix.get(i, j) << ", ";
        }
        out << "]";
    }
    return out << "]";
}

#endif
