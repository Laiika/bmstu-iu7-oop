#ifndef RETURN_CODES_H
#define RETURN_CODES_H

#include <QMessageBox>

enum return_codes
{
    OK,
    UNKNOWN_COMMAND,
    FILE_ERROR,
    MEMORY_ERROR,
    SIZE_ERROR,
    INPUT_ERROR,
    NO_FIGURE
};
typedef return_codes rc_t;


void error_print(rc_t error);

#endif // RETURN_CODES_H
