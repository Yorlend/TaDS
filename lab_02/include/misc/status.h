#ifndef _STATUS_H_
#define _STATUS_H_


typedef enum
{
    SUCCESS,            // Успешное завершение работы
    FILE_ERROR,         // Ошибка чтения файла
    TABLE_ERROR,        // Ошибка работы с таблицей
    INPUT_ERROR,        // Ошибка ввода
    MEMORY_ERROR,       // Ошибка памяти
    STUD_ERROR,         // Ошибка: некорректный студент
    FUNC_ARGS_ERROR,    // Ошибка аргументов функции
} status_t;

#endif // _STATUS_H_