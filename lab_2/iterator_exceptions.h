#ifndef ITERATOR_EXCEPTIONS_H
#define ITERATOR_EXCEPTIONS_H

#include "base_exception.h"

class ItIndexException : public BaseException
{
public:
    ItIndexException(const std::string &time, const std::string &fileName,
                   const int line, const std::string &className,
                   const std::string &methodName,
                   const std::string &msg = "Iterator index is out of range!")
  : BaseException(time, fileName, line, className, methodName, msg){};
};

class ExpiredException : public BaseException
{
public:
    ExpiredException(const std::string &time, const std::string &fileName,
                     const int line, const std::string &className,
                     const std::string &methodName,
                     const std::string &msg = "Expired weak pointer!")
    : BaseException(time, fileName, line, className, methodName, msg){};
};


#endif // ITERATOR_EXCEPTIONS_H
