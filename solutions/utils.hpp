#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <format>

std::vector<std::string> split(const std::string& s, char delim = ' ') {
    std::istringstream iss{s};
    std::string token;
    std::vector<std::string> out{};
    while (std::getline(iss, token, delim)) {
        if (!token.empty()) {
            out.push_back(token);
        }
    }
    return out;
}

template<class T>
class Grid {
public:
    // Constructor for an empty grid
    Grid() : m_rows{0}, m_cols{0} {}

    // Constructor with specified dimensions and default value
    Grid(size_t rows, size_t cols, const T& value = T()) : m_rows{rows}, m_cols{cols}, m_grid(rows * cols, value) {}

    [[nodiscard]] size_t rows() const { return m_rows; }

    [[nodiscard]] size_t cols() const { return m_cols; }

    T& operator[](size_t r, size_t c) {
        check_bounds(r, c);
        return (m_grid[m_cols * r + c]);
    }

    const T& operator[](size_t r, size_t c) const {
        check_bounds(r, c);
        return m_grid[m_cols * r + c];
    }

    T& operator[](std::pair<size_t, size_t> const& p) {
        check_bounds(p.first, p.second);
        return m_grid[m_cols * p.first + p.second];
    }

    const T& operator[](std::pair<size_t, size_t> const& p) const {
        check_bounds(p.first, p.second);
        return m_grid[m_cols * p.first + p.second];
    }

    void push_row(std::vector<T> const& row) {
        push_row_impl(row.begin(), row.end());
    }

    void push_row(std::vector<T>&& row) {
        push_row_impl(std::make_move_iterator(row.begin()), std::make_move_iterator(row.end()));
    }

    void push_row(std::initializer_list<T> row) {
        push_row_impl(row.begin(), row.end());
    }

private:
    template<typename InputIt>
    void push_row_impl(InputIt first, InputIt last) {
        size_t new_row_size = std::distance(first, last);
        if (m_rows == 0) {
            m_cols = new_row_size;  // Set the number of columns based on the first row
        } else if (new_row_size != m_cols) {
            throw std::runtime_error{std::format("incorrect row size: expected {}, got {}", m_cols, new_row_size)};
        }
        ++m_rows;
        m_grid.insert(m_grid.end(), first, last);
    }

public:


    // Nested struct for iterator dereference
    struct IteratorValue {
        size_t r;  // Column
        size_t c;  // Row
        T& value;  // Reference to the value

        T& operator*() { return value; }

        const T& operator*() const { return value; }
    };

    // Custom random access iterator
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = IteratorValue;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        // Constructor
        Iterator(size_t rows, size_t cols, typename std::vector<T>::iterator base, size_t current = 0) : m_rows(rows),
                                                                                                         m_cols(cols),
                                                                                                         m_base(base),
                                                                                                         m_current(
                                                                                                                 current) {}

        // Dereference operator
        IteratorValue operator*() const {
            size_t row = m_current / m_cols;
            size_t col = m_current % m_cols;
            return {row, col, *(m_base + m_current)};
        }

        // Increment and decrement
        Iterator& operator++() {
            ++m_current;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            --m_current;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // Arithmetic operations
        Iterator& operator+=(difference_type n) {
            m_current += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            m_current -= n;
            return *this;
        }

        Iterator operator+(difference_type n) const { return Iterator(m_rows, m_cols, m_base, m_current + n); }

        Iterator operator-(difference_type n) const { return Iterator(m_rows, m_cols, m_base, m_current - n); }

        difference_type operator-(const Iterator& other) const { return m_current - other.m_current; }

        // Random access
        IteratorValue operator[](difference_type n) const { return *(*this + n); }

        // Comparisons
        bool operator==(const Iterator& other) const { return m_current == other.m_current; }

        bool operator!=(const Iterator& other) const { return !(*this == other); }

        bool operator<(const Iterator& other) const { return m_current < other.m_current; }

        bool operator<=(const Iterator& other) const { return m_current <= other.m_current; }

        bool operator>(const Iterator& other) const { return m_current > other.m_current; }

        bool operator>=(const Iterator& other) const { return m_current >= other.m_current; }

    private:
        size_t m_rows;
        size_t m_cols;
        typename std::vector<T>::iterator m_base;  // Base iterator of the vector
        size_t m_current;                          // Current position in the grid
    };

    template <class S>
    friend std::ostream& operator<<(std::ostream& os, const Grid<S>& grid);

    // Begin and end methods
    Iterator begin() { return Iterator(m_rows, m_cols, m_grid.begin(), 0); }

    Iterator end() { return Iterator(m_rows, m_cols, m_grid.begin(), m_rows * m_cols); }

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<T> m_grid;

    void check_bounds(size_t r, size_t c) const {
        if (r >= m_rows || c >= m_cols) {
            throw std::out_of_range{std::format("index {},{} out of range", r, c)};
        }
    }
};

template <class S>
std::ostream& operator<<(std::ostream& os, const Grid<S>& grid) {
    auto it = grid.m_grid.begin();  // Iterator to the first element
    for (size_t r = 0; r < grid.m_rows; ++r) {
        for (size_t c = 0; c < grid.m_cols; ++c) {
            if (*it == '@') {
                std::cout << "\033[31;1m@\033[0m";
            } else {
                os << *it;
            }
            ++it;
        }
        os << "\n";
    }
    return os;
}


