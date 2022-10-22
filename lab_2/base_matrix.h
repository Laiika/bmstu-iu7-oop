#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H

#include <cstddef>

class BaseMatrix
{
public:
    BaseMatrix();
    BaseMatrix(const size_t rows, const size_t cols);
    virtual ~BaseMatrix() = 0;

    bool is_empty() const;
    size_t get_rows() const;
    size_t get_columns() const;

protected:
    size_t rows = 0;
    size_t columns = 0;
};

#endif // BASE_MATRIX_H
