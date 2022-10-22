#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include "base_exception.h"

class IndexException : public BaseException
{
public:
    IndexException(const std::string &time, const std::string &fileName,
                   const int line, const std::string &className,
                   const std::string &methodName,
                   const std::string &msg = "Index is out of range!")
  : BaseException(time, fileName, line, className, methodName, msg){};
};

class SizesException : public BaseException
{
public:
    SizesException(const std::string &time, const std::string &fileName,
                   const int line, const std::string &className,
                   const std::string &methodName,
                   const std::string &msg = "Operation with matrices of incorrect sizes!")
  : BaseException(time, fileName, line, className, methodName, msg){};
};

class DivisionByZeroException : public BaseException
{
public:
    DivisionByZeroException(const std::string &time, const std::string &fileName,
                   const int line, const std::string &className,
                   const std::string &methodName,
                   const std::string &msg = "Division by zero!")
  : BaseException(time, fileName, line, className, methodName, msg){};
};

class SquareSizeException : public BaseException
{
public:
    SquareSizeException(const std::string &time, const std::string &fileName,
                       const int line, const std::string &className,
                       const std::string &methodName,
                       const std::string &msg = "Matrix must be square!")
      : BaseException(time, fileName, line, className, methodName, msg){};
};

class ZeroDetException : public BaseException
{
public:
    ZeroDetException(const std::string &time, const std::string &fileName,
                       const int line, const std::string &className,
                       const std::string &methodName,
                       const std::string &msg = "Det = 0!")
      : BaseException(time, fileName, line, className, methodName, msg){};
};

class MemoryException : public BaseException
{
public:
    MemoryException(const std::string &time, const std::string &fileName,
                      const int line, const std::string &className,
                      const std::string &methodName,
                      const std::string &msg = "Memory allocation error!")
     : BaseException(time, fileName, line, className, methodName, msg){};
};

#endif // MATRIX_EXCEPTIONS_H
