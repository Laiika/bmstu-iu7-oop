#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix.h"
#include "matrix_exceptions.h"

#include <initializer_list>
#include <iostream> // for endl

#define EPS 1E-9

// CONSTRUCTORS

template <typename T>
Matrix<T>::Matrix() noexcept: BaseMatrix() {}

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t cols): BaseMatrix(rows, cols)
{
    allocate(rows * cols);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &mtr): BaseMatrix(mtr.rows, mtr.columns)
{
    allocate(mtr.rows * mtr.columns);

    for (size_t i = 0; i < rows * columns; i++)
        data[i] = mtr.data[i];
}

template <typename T>
Matrix<T>::Matrix(const T **mtr, const size_t rows, const size_t cols): BaseMatrix(rows, cols)
{
    allocate(rows * cols);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i * cols + j] = mtr[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&mtr) noexcept: BaseMatrix(mtr.rows, mtr.columns)
{
    this->data = mtr.data;
    mtr.data.reset();
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> elems): BaseMatrix(elems.size(), elems.begin()->size())
{
    allocate(this->rows * this->columns);

    auto elem_i = elems.begin();

    for (size_t i = 0; elem_i < elems.end(); i++, elem_i++)
    {
        auto elem_j = elem_i->begin();

        for (size_t j = 0; elem_j < elem_i->end(); j++, elem_j++)
            data[i * columns + j] = *elem_j;
    }
}

//ASSIGNMENT

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mtr)
{
    this->rows = mtr.rows;
    this->columns = mtr.columns;
    allocate(mtr.rows * mtr.columns);

    for (size_t i = 0; i < rows * columns; i++)
        data[i] = mtr.data[i];

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mtr) noexcept
{
    this->rows = mtr.rows;
    this->columns = mtr.columns;
    this->data = mtr.data;
    mtr.data.reset();

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> elems)
{
    this->rows = elems.size();
    this->columns = elems.begin()->size();
    allocate(this->rows * this->columns);

    auto elem_i = elems.begin();

    for (size_t i = 0; elem_i < elems.end(); i++, elem_i++)
    {
        auto elem_j = elem_i->begin();

        for (size_t j = 0; j < elem_i->end(); j++, elem_j++)
            data[i * columns + j] = *elem_j;
    }

    return *this;
}

// COMPARISON

template <typename T>
bool Matrix<T>::is_equal(const Matrix<T> &mtr) const
{
    if (rows != mtr.rows || columns != mtr.columns)
        return false;

    for (size_t i = 0; i < rows * columns; i++)
        if (data[i] != mtr.data[i])
                return false;

    return true;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &mtr) const
{
    return is_equal(mtr);
}

template <typename T>
bool Matrix<T>::is_not_equal(const Matrix<T> &mtr) const
{
    return !is_equal(mtr);
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T> &mtr) const
{
    return !is_equal(mtr);
}

// INDEXATIONS

template <typename T>
T& Matrix<T>::at(const size_t i, const size_t j)
{
    row_index_check(i, __LINE__);
    col_index_check(j, __LINE__);
    return data[i * columns + j];
}

template <typename T>
T& Matrix<T>::operator()(const size_t i, const size_t j)
{
    return at(i, j);
}

template <typename T>
const T& Matrix<T>::at(const size_t i, const size_t j) const
{
    row_index_check(i, __LINE__);
    col_index_check(j, __LINE__);
    return data[i * columns + j];
}

template <typename T>
const T& Matrix<T>::operator()(const size_t i, const size_t j) const
{
    return at(i, j);
}

// ADDITION

template <typename T>
Matrix<T> Matrix<T>::add_mtr(const Matrix<T> &mtr) const
{
    sum_sizes_check(mtr, __LINE__);

    Matrix<T> res(*this);

    for (size_t i = 0; i < rows * columns; i++)
        res.data[i] += mtr.data[i];

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mtr) const
{
    return add_mtr(mtr);
}

template <typename T>
Matrix<T> Matrix<T>::add_num(const T &value) const
{
    Matrix<T> res(*this);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            res.data[i * columns + j] += value;

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T &value) const
{
    return add_num(value);
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &mtr)
{
    sum_sizes_check(mtr, __LINE__);

    for (size_t i = 0; i < rows * columns; i++)
        data[i] += mtr.data[i];

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T &value)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            data[i * columns + j] += value;

    return *this;
}

// SUBSTRACTION

template <typename T>
Matrix<T> Matrix<T>::sub_mtr(const Matrix<T> &mtr) const
{
    sum_sizes_check(mtr, __LINE__);

    Matrix<T> res(*this);

    for (size_t i = 0; i < rows * columns; i++)
        res.data[i] -= mtr.data[i];

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &mtr) const
{
    return sub_mtr(mtr);
}

template <typename T>
Matrix<T> Matrix<T>::sub_num(const T &value) const
{
    Matrix<T> res(*this);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            res.data[i * columns + j] -= value;

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T &value) const
{
    return sub_num(value);
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &mtr)
{
    sum_sizes_check(mtr, __LINE__);

    for (size_t i = 0; i < rows * columns; i++)
        data[i] -= mtr.data[i];

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T &value)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            data[i * columns + j] -= value;

    return *this;
}

// MULTIPLICATION

template <typename T>
Matrix<T> Matrix<T>::mul_mtr(const Matrix<T> &mtr) const
{
    mul_sizes_check(mtr, __LINE__);

    Matrix<T> res(rows, mtr.columns);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < mtr.columns; j++)
        {
            T sum = 0;

            for (size_t k = 0; k < columns; k++)
                sum += this->at(i, k) * mtr.at(k, j);

            res.data[i * mtr.columns + j] = sum;
        }
    }

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &mtr) const
{
    return mul_mtr(mtr);
}

template <typename T>
Matrix<T> Matrix<T>::mul_num(const T &value) const
{
    Matrix<T> res(*this);

    for (size_t i = 0; i < res.rows; i++)
        for (size_t j = 0; j < res.columns; j++)
            res.data[i * columns + j] *= value;

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &value) const
{
    return mul_num(value);
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &mtr)
{
    Matrix<T> res = (*this) * mtr;
    *this = res;

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T &value)
{
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            data[i * columns + j] *= value;

    return *this;
}

// DIVISION

template <typename T>
Matrix<T> Matrix<T>::div_mtr(const Matrix<T> &mtr) const
{
    return mul_mtr(mtr.inverted());
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T> &mtr) const
{
    return mul_mtr(mtr.inverted());
}

template <typename T>
Matrix<T> Matrix<T>::div_num(const T &value) const
{
    division_by_zero_check(value, __LINE__);

    Matrix<T> res(*this);

    for (size_t i = 0; i < res.rows; i++)
        for (size_t j = 0; j < res.columns; j++)
            res.data[i * columns + j] /= value;

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T &value) const
{
    return div_num(value);
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix<T> &mtr)
{
    Matrix<T> tmp = operator/(mtr);
    *this = tmp;

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T &value)
{
    division_by_zero_check(value, __LINE__);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            data[i * columns + j] /= value;

    return (*this);
}

// ITERATORS

template <typename T>
Iterator<T> Matrix<T>::begin()
{
    Iterator<T> iter(*this);

    return iter;
}

template <typename T>
Iterator<T> Matrix<T>::end()
{
    Iterator<T> iter(*this);

    return iter + rows * columns;
}

template <typename T>
ConstIterator<T> Matrix<T>::begin() const
{
    ConstIterator<T> iter(*this);

    return iter;
}

template <typename T>
ConstIterator<T> Matrix<T>::end() const
{
    ConstIterator<T> iter(*this);

    return iter + rows * columns;
}

template <typename T>
ConstIterator<T> Matrix<T>::cbegin() const
{
    ConstIterator<T> iter(*this);

    return iter;
}

template <typename T>
ConstIterator<T> Matrix<T>::cend() const
{
    ConstIterator<T> iter(*this);

    return iter + rows * columns;
}

// OTHER METHODS

template <typename T2>
std::ostream& operator<<(std::ostream& os, const Matrix<T2>& mtr)
{
    for (size_t i = 0; i < mtr.get_rows(); i++)
    {
        for (size_t j = 0; j < mtr.get_columns(); j++)
            os << mtr.data[i * mtr.columns + j]  << "\t";

        os << std::endl;
    }

    return os;
}

template <typename T>
Matrix<T> Matrix<T>::zero_matrix(const size_t rows, const size_t cols)
{
    Matrix<T> mtr(rows, cols);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            mtr.data[i * cols + j] = 0;

    return mtr;
}

template <typename T>
Matrix<T> Matrix<T>::identity_matrix(const size_t rows, const size_t cols)
{
    Matrix<T> mtr(rows, cols);

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            mtr.data[i * cols + j] = (i == j);

    return mtr;
}

template <typename T>
void Matrix<T>::swap_rows(const size_t i, const size_t j)
{
    row_index_check(i, __LINE__);
    row_index_check(j, __LINE__);

    if (i != j)
        for (size_t clm = 0; clm < columns; clm++)
            std::swap(at(i, clm), at(j, clm));
}

template <typename T>
void Matrix<T>::exclude_copy(Matrix<T>& dst, const Matrix<T>& src, const size_t ex_row, const size_t ex_col)
{
    size_t row_index, col_index;

    for (size_t i = 0; i < src.get_rows() - 1; i++)
        for (size_t j = 0; j < src.get_columns() - 1; j++)
        {
            row_index = i >= ex_row ? i + 1 : i;
            col_index = j >= ex_col ? j + 1 : j;
            dst.data[i * src.get_columns() + j] = src.data[row_index * src.get_columns() + col_index];
        }
}

template <typename T>
Matrix<T> Matrix<T>::inverted() const
{
    square_sizes_check(__LINE__);
    det_check(__LINE__);

    Matrix<T> res(rows, columns);
    Matrix<T> tmp(rows - 1, columns - 1);
    T value = {};
    T det = this->det();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
        {
            Matrix<T>::exclude_copy(tmp, *this, i, j);
            value = tmp.det() / det;

            if ((i + j) & 1)
                value = -value;

            res(j, i) = value;
        }

    return res;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> tr_mtr(columns, rows);

    for (size_t row = 0; row < rows; row++)
        for (size_t clm = 0; clm < columns; clm++)
            tr_mtr.at(clm, row) = at(row, clm);

    return tr_mtr;
}

template <typename T>
T Matrix<T>::det() const
{ 
    square_sizes_check(__LINE__);

    if (get_rows() == 2)
        return data[0] * data[3] - data[2] * data[1];
    if (get_rows() == 1)
        return data[0];

    Matrix<T> tmp(get_rows() - 1, get_columns() - 1);
    T res = {};

    for (size_t i = 0; i < get_rows(); i++)
    {
        Matrix<T>::exclude_copy(tmp, *this, 0, i);
        T minor = tmp.det();

        if (i % 2 == 1)
            minor = -minor;

        res += minor * data[i];
    }

    return res;
}

template <typename T>
void Matrix<T>::allocate(const size_t size)
{
    time_t cur_time = time(NULL);
    int line;

    try
    {
        line = __LINE__;
        data.reset(new T[size]);
    }
    catch (std::bad_alloc &err)
    {
        throw MemoryException(ctime(&cur_time), __FILE__, line,
                                typeid(*this).name(), __FUNCTION__);
    }
}

// CHECKS

template <typename T>
void Matrix<T>::row_index_check(const size_t i, const int line) const
{
    if (i >= get_rows())
    {
        time_t cur_time = time(NULL);
        throw IndexException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template <typename T>
void Matrix<T>::col_index_check(const size_t j, const int line) const
{
    if (j >= get_columns())
    {
        time_t cur_time = time(NULL);
        throw IndexException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template <typename T>
void Matrix<T>::square_sizes_check(const int line) const
{
    if (get_rows() != get_columns())
    {
        time_t cur_time = time(NULL);
        throw SquareSizeException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template <typename T>
void Matrix<T>::det_check(const int line) const
{
    T det = this->det();

    if (!det)
    {
        time_t cur_time = time(NULL);
        throw ZeroDetException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template <typename T>
void Matrix<T>::sum_sizes_check(const Matrix<T> &mtr, const int line) const
{
    if (get_rows() != mtr.get_rows() || get_columns() != mtr.get_columns())
    {
        time_t cur_time = time(NULL);
        throw SizesException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template <typename T>
void Matrix<T>::mul_sizes_check(const Matrix<T> &mtr, const int line) const
{
    if (get_columns() != mtr.get_rows())
    {
        time_t cur_time = time(NULL);
        throw SizesException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

template <typename T>
void Matrix<T>::division_by_zero_check(const T &num, const int line) const
{
    if (abs(num) < EPS)
    {
        time_t cur_time = time(NULL);
        throw DivisionByZeroException(ctime(&cur_time), __FILE__,
                                  line, typeid(*this).name(),
                                  __FUNCTION__);
    }
}

#endif // MATRIX_HPP
