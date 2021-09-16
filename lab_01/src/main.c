#include <stdio.h>
#include "status_code.h"
#include "console_io.h"


int main(void)
{
    status_t exit_code = SUCCESS;
    exp_float_t num;

    exit_code = input_number(&num);

    if (exit_code == SUCCESS)
        output_number(&num);

    else
        print_status(exit_code);
    return exit_code;
}
