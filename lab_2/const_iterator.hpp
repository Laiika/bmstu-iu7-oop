#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <time.h>
#include "const_iterator.h"
#include "iterator_exceptions.h"

template <typename T>
ConstIterator<T>::ConstIterator(const Matrix<T> &mtr) noexcept
{
    ptr = mtr.data;
    index = 0;
    rows = mtr.rows;
    columns = mtr.columns;
}

template <typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &iterator) noexcept
{
    ptr = iterator.ptr;
    index = iterator.index;
    rows = iterator.rows;
    columns = iterator.columns;
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &iterator) noexcept
{
    ptr.reset(iterator.ptr);
    index = iterator.index;
    rows = iterator.rows;
    columns = iterator.columns;
}

template <typename T>
ConstIterator<T>::operator bool() const
{
    expride_check(__LINE__);

    return rows && (index < rows * columns);
}

template <typename T>
const T& ConstIterator<T>::operator*() const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    return *get_ptr();
}

template <typename T>
const T* ConstIterator<T>::operator->() const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    return get_ptr();
}

template <typename T>
const T& ConstIterator<T>::operator[](const size_t offset) const
{
    expride_check(__LINE__);
    index_check(__LINE__, offset);

    return *(get_ptr() + offset);
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator+(const size_t val) const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ConstIterator<T> tmp(*this);
    tmp.index += val;
    return tmp;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::operator+=(const size_t val)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    index += val;
    return *this;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::operator++()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ++index;
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ConstIterator<T> tmp(*this);
    ++index;
    return tmp;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator-(const size_t val) const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ConstIterator<T> tmp(*this);
    tmp.index -= val;
    return tmp;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::operator-=(const size_t val)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    index -= val;
    return *this;
}

template <typename T>
ConstIterator<T>& ConstIterator<T>::operator--()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    --index;
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator--(int)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ConstIterator<T> tmp(*this);
    --index;
    return tmp;
}


template <typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &iterator) const
{
    expride_check(__LINE__);
    iterator.expride_check(__LINE__);

    return get_ptr() == iterator.get_ptr();
}

template <typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &iterator) const
{
    return !(*this == iterator);
}

template <typename T>
bool ConstIterator<T>::operator>(const ConstIterator<T> &iterator) const
{
    expride_check(__LINE__);
    iterator.expride_check(__LINE__);

    return get_ptr() > iterator.get_ptr();
}

template <typename T>
bool ConstIterator<T>::operator>=(const ConstIterator<T> &iterator) const
{
    return !(iterator.get_ptr() > get_ptr());
}

template <typename T>
bool ConstIterator<T>::operator<(const ConstIterator<T> &iterator) const
{
    return iterator.get_ptr() > get_ptr();
}

template <typename T>
bool ConstIterator<T>::operator<=(const ConstIterator<T> &iterator) const
{
    return !(get_ptr() > iterator.get_ptr());
}

template <typename T>
T* ConstIterator<T>::get_ptr() const
{
    shared_ptr<T[]> tmp = ptr.lock();
    return tmp.get() + index;
}

template <typename T>
void ConstIterator<T>::expride_check(const int line) const
{
    if (ptr.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T>
void ConstIterator<T>::index_check(const int line) const
{
    if (index >= rows * columns)
    {
        time_t curTime = time(NULL);
        throw ItIndexException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __FUNCTION__);
    }
}

#endif // CONST_ITERATOR_HPP
