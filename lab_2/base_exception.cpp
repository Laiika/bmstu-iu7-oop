#include "base_exception.h"

BaseException::BaseException(const std::string &time, const std::string &fileName,
                             const int line, const std::string &className,
                             const std::string &methodName, const std::string &msg = "Error!")
{
    error_msg = "\nTime:   " + time + "File:   " + fileName +
                "\nLine:   " + std::to_string(line) + "\nClass:  " + className +
                "\nMethod: " + methodName + "\nMsg:   " + msg + "\n";
}

const char* BaseException::what() const noexcept
{
    return error_msg.c_str();
}
