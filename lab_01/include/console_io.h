#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "status_code.h"
#include "exp_float.h"


void print_rules();
status_t input_number(exp_float_t* num);
void output_number(const exp_float_t* num);

#endif // CONSOLE_IO_H
