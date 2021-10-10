#ifndef _AUTOTABLE_H_
#define _AUTOTABLE_H_

#include <stdbool.h>
#include <stdio.h>
#include "student.h"
#include "misc/status.h"
#include "keytable.h"
#include "misc/sort.h"


typedef struct studtable
{
    student_t* data;
    unsigned int size;
} studtable_t;


// Функция возвращает пустую таблицу
studtable_t stable_empty();

// Функция резервирует память под таблицу
studtable_t stable_reserve(unsigned int size);

// Функция освобождает ресурсы
void stable_destroy(studtable_t* table);

// Функция проверки таблицы на валидность
bool stable_valid(const studtable_t* table);

// Функция загрузки таблицы по имени файла
status_t stable_load(studtable_t* table, const char* filename);

// Функция загрузки таблицы по файловому указателю
status_t stable_loadf(studtable_t* table, FILE* file);

// Функция добавления студента
status_t stable_push_back(studtable_t* table, const student_t* stud);

// Функция удаления студента
status_t stable_remove(studtable_t* table, size_t id);

// Функция вывода таблицы студентов
void stable_print(const studtable_t* table);

// Функция вывода студентов указанного года поступления, живущих в общежитии
void stable_cond_print(studtable_t* table, uint16_t year);

// Функция вывода студентов по таблице ключей
void stable_print_key(const studtable_t* table, const keytable_t* kt);

// Функция сортировки таблицы
void stable_sort(studtable_t* table, sort_t sort_fn);


#endif // _AUTOTABLE_H_
