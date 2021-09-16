#include <stdio.h>
#include "status_code.h"
#include "console_io.h"


int main(void)
{
    status_t exit_code = SUCCESS;
    exp_float_t num1, num2, res;

    exit_code = input_number(&num1);

    if (exit_code == SUCCESS)
        exit_code = input_number(&num2);

    if (exit_code == SUCCESS)
        exit_code = multiply(&res, &num1, &num2);

    if (exit_code == SUCCESS)
        output_number(&res);

    else
        print_status(exit_code);

    return exit_code;
}
