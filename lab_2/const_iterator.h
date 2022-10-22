#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>

using namespace std;

template <typename T> class Matrix;

template <typename T>
class ConstIterator : public iterator<random_access_iterator_tag, T>
{
    friend class Matrix<T>;

public:
    ConstIterator(const Matrix<T> &mtr) noexcept;
    ConstIterator(const ConstIterator<T> &iterator) noexcept;

    ~ConstIterator() = default;

    ConstIterator<T>& operator=(const ConstIterator<T> &iterator) noexcept;

    operator bool() const;

    const T& operator*() const;
    const T* operator->() const;
    const T& operator[](const size_t offset) const;

    ConstIterator<T> operator+(const size_t val) const;
    ConstIterator<T>& operator+=(const size_t val);

    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);

    ConstIterator<T> operator-(const size_t val) const;
    ConstIterator<T>& operator-=(const size_t val);

    ConstIterator<T>& operator--();
    ConstIterator<T> operator--(int);

    bool operator==(const ConstIterator<T> &iterator) const;
    bool operator!=(const ConstIterator<T> &iterator) const;

    bool operator>(const ConstIterator<T> &iterator) const;
    bool operator>=(const ConstIterator<T> &iterator) const;

    bool operator<(const ConstIterator<T> &iterator) const;
    bool operator<=(const ConstIterator<T> &iterator) const;

protected:
    T* get_ptr() const;
    void expride_check(const int line) const;
    void index_check(const int line) const;

private:
    weak_ptr<T[]> ptr;

    size_t index = 0;
    size_t rows = 0;
    size_t columns = 0;
};

#include "const_iterator.hpp"

#endif // CONST_ITERATOR_H
