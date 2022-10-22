#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

using namespace std;

template <typename T> class Matrix;

template <typename T>
class Iterator : public iterator<random_access_iterator_tag, T>
{
    friend class Matrix<T>;

public:
    Iterator(const Matrix<T> &mtr) noexcept;
    Iterator(const Iterator<T> &iterator) noexcept;

    ~Iterator() = default;

    Iterator<T>& operator=(const Iterator<T> &iterator) noexcept;

    operator bool() const;

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    T& operator[](const size_t offset);
    const T& operator[](const size_t offset) const;

    Iterator<T> operator+(const size_t val) const;
    Iterator<T>& operator+=(const size_t val);

    Iterator<T>& operator++();
    Iterator<T> operator++(int);

    Iterator<T> operator-(const size_t val) const;
    Iterator<T>& operator-=(const size_t val);

    Iterator<T>& operator--();
    Iterator<T> operator--(int);

    bool operator==(const Iterator<T> &iterator) const;
    bool operator!=(const Iterator<T> &iterator) const;

    bool operator>(const Iterator<T> &iterator) const;
    bool operator>=(const Iterator<T> &iterator) const;

    bool operator<(const Iterator<T> &iterator) const;
    bool operator<=(const Iterator<T> &iterator) const;

protected:
    T* get_ptr() const;
    void expride_check(const int line) const;
    void index_check(const int line) const;

private:
    weak_ptr<T[]> ptr;
    size_t rows = 0;
    size_t columns = 0;
    size_t index = 0;
};

#include "iterator.hpp"

#endif // ITERATOR_H
