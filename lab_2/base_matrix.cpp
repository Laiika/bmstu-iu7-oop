#include <iostream>

#include "base_matrix.h"

BaseMatrix::BaseMatrix()
{
    rows = 0;
    columns = 0;
}

BaseMatrix::BaseMatrix(const size_t rows_val, const size_t cols_val)
{
    rows = rows_val;
    columns = cols_val;
}

bool BaseMatrix::is_empty() const
{
    return rows * columns == 0;
}

size_t BaseMatrix::get_rows() const
{
    return rows;
}

size_t BaseMatrix::get_columns() const
{
    return columns;
}

BaseMatrix::~BaseMatrix() = default;
