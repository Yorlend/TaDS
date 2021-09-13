#ifndef STATUS_CODE_H
#define STATUS_CODE_H

typedef enum status
{
    SUCCESS,
    INPUT_ERROR,
    OVERFLOW_ERROR
} status_t;

void print_status(status_t status);

#endif // STATUS_CODE_H
