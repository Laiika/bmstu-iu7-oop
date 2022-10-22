#ifndef MATRIX_H
#define MATRIX_H

#include "base_matrix.h"
#include "const_iterator.h"
#include "iterator.h"

#include <initializer_list>
#include <memory>

template <typename T>
class Matrix : public BaseMatrix
{
public:
    friend Iterator<T>;
    friend ConstIterator<T>;

    // CONSTRUCTORS
    Matrix() noexcept;
    explicit Matrix(const size_t rows, const size_t cols);
    explicit Matrix(const Matrix<T> &mtr);
    Matrix(const T **mtr, const size_t rows, const size_t cols);
    Matrix(Matrix<T> &&mtr) noexcept;
    Matrix(const std::initializer_list<std::initializer_list<T>> elems);

    // DESTRUCTORS
    ~Matrix() override = default;

    // ASSIGNMENT
    Matrix<T>& operator=(const Matrix<T> &mtr);
    Matrix<T>& operator=(Matrix<T> &&mtr) noexcept;
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> elems);

    // COMPARISON
    bool is_equal(const Matrix<T> &mtr) const;
    bool operator==(const Matrix<T> &mtr) const;
    bool is_not_equal(const Matrix<T> &mtr) const;
    bool operator!=(const Matrix<T> &mtr) const;

    // INDEXATIONS
    T& at(const size_t i, const size_t j);
    T& operator()(const size_t i, const size_t j);
    const T& at(const size_t i, const size_t j) const;
    const T& operator()(const size_t i, const size_t j) const;

    // ADDITION
    Matrix<T> add_mtr(const Matrix<T> &mtr) const;
    Matrix<T> operator+(const Matrix<T> &mtr) const;
    Matrix<T> add_num(const T &value) const;
    Matrix<T> operator+(const T &value) const;
    Matrix<T>& operator+=(const Matrix<T> &mtr);
    Matrix<T>& operator+=(const T &value);

    // SUBSTRACTION
    Matrix<T> sub_mtr(const Matrix<T> &mtr) const;
    Matrix<T> operator-(const Matrix<T> &mtr) const;
    Matrix<T> sub_num(const T &value) const;
    Matrix<T> operator-(const T &value) const;
    Matrix<T>& operator-=(const Matrix<T> &mtr);
    Matrix<T>& operator-=(const T &value);

    // MULTIPLICATION
    Matrix<T> mul_mtr(const Matrix<T> &mtr) const;
    Matrix<T> operator*(const Matrix<T> &mtr) const;
    Matrix<T> mul_num(const T &value) const;
    Matrix<T> operator*(const T &value) const;
    Matrix<T>& operator*=(const Matrix<T> &mtr);
    Matrix<T>& operator*=(const T &value);

    // DIVISION
    Matrix<T> div_mtr(const Matrix<T> &mtr) const;
    Matrix<T> operator/(const Matrix<T> &mtr) const;
    Matrix<T> div_num(const T &value) const;
    Matrix<T> operator/(const T &value) const;
    Matrix<T>& operator/=(const Matrix<T> &mtr);
    Matrix<T>& operator/=(const T &value);

    // ITERATORS
    Iterator<T> begin();
    Iterator<T> end();

    ConstIterator<T> begin() const;
    ConstIterator<T> end() const;
    ConstIterator<T> cbegin() const;
    ConstIterator<T> cend() const;

    // OTHER METHODS
    template <typename T2>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T2>& mtr);

    static Matrix<T> zero_matrix(const size_t rows, const size_t cols);
    static Matrix<T> identity_matrix(const size_t rows, const size_t cols);

    void swap_rows(const size_t i, const size_t j);
    Matrix<T> inverted() const;
    Matrix<T> transpose() const;
    T det() const;

protected:
    void allocate(const size_t size);

    // CHECKS
    void row_index_check(const size_t i, const int line) const;
    void col_index_check(const size_t j, const int line) const;
    void square_sizes_check(const int line) const;
    void det_check(const int line) const;
    void sum_sizes_check(const Matrix<T> &mtr, const int line) const;
    void mul_sizes_check(const Matrix<T> &mtr, const int line) const;
    void division_by_zero_check(const T &num, const int line) const;

    static void exclude_copy(Matrix<T>& dst, const Matrix<T>& src, const size_t ex_row, const size_t ex_col);

private:
    std::shared_ptr<T[]> data = nullptr;
};

#include "matrix.hpp"

#endif // MATRIX_H
