#ifndef ERRORS_H
#define ERRORS_H

#include <QMessageBox>

enum errors
{
    SUCCESS,
    FILE_ERROR,
    ALLOCATION_ERROR,
    READ_ERROR,
    LSIZE_ERROR,
    PSIZE_ERROR,
    MEMORY_ERROR,
    UNKNOWN_COMMAND
};

using err_t = enum errors;

int errors(const err_t &code);

#endif
