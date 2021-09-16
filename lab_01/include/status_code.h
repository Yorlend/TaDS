#ifndef STATUS_CODE_H
#define STATUS_CODE_H

typedef enum status
{
    SUCCESS,            // Успешное завершение
    INPUT_ERROR,        // Недопустимые символы
    MANTISSA_OVERFLOW,  // Переполнение мантиссы при вводе
    DEGREE_OVERFLOW,    // Переполнение степени числа
    DEGREE_UNDERFLOW,   // Машинный нуль
    OVERFLOW_ERROR,     // Переполнение буфера
    POINTS_ERROR,       // Более одной точки
    EMPTY_ERROR         // Встречена пустая мантисса
} status_t;

void print_status(status_t status);

#endif // STATUS_CODE_H
