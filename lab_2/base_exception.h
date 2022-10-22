#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <string>

class BaseException : public std::exception
{
public:
    BaseException(const std::string &time, const std::string &fileName,
                  const int line, const std::string &className,
                  const std::string &methodName, const std::string &msg);

    virtual const char* what(void) const noexcept;

protected:
    std::string error_msg;
};

#endif // BASE_EXCEPTION_H
