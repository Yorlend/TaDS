#include <stdio.h>
#include "status_code.h"
#include "console_io.h"


int main(void)
{
    status_t exit_code = SUCCESS;
    exp_float_t num;

    input_number(&num);
    output_number(&num);

    return exit_code;
}
