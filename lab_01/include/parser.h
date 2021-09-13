#ifndef PARSER_H
#define PARSER_H

#include "status_code.h"
#include "exp_float.h"


status_t parse_exp_float(exp_float_t* num, const char* str);

#endif // PARSER_H
