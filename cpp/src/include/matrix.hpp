#ifndef AOC_MATRIX_HPP
#define AOC_MATRIX_HPP

#include <iostream>
#include <vector>

template<typename T>
struct matrix
{
    matrix() = default;
    matrix(matrix&&) noexcept = default;

    [[nodiscard]] auto get(int i, int j) const -> T { return m_[i][j]; }

    void set(int i, int j, const T& v)
    {
        ensure_size(i, j);
        m_[i][j] = v;
    }

    [[nodiscard]] auto rows() const -> int { return m_.size(); }

    [[nodiscard]] auto columns(int row) const -> int { return m_[row].size(); }

    void remove_rows(int new_size) { m_.resize(new_size); }

    void remove_columns(int new_size)
    {
        for (auto& r : m_) {
            r.resize(new_size);
        }
    }

  private:
    void ensure_size(int i, int j)
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
