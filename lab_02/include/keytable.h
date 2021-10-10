#ifndef __KEYTABLE_H__
#define __KEYTABLE_H__

#include "key.h"
#include "misc/status.h"
#include "misc/sort.h"

typedef struct studtable studtable_t;

typedef struct keytable
{
    _key_t* data;
    size_t size;
} keytable_t;


// Инициализирует таблицу ключей нулевыми значениями
status_t init_keytable(keytable_t* kt);

// Обновляет таблицу ключей в соответствии с таблицей студентов
status_t update_keytable(keytable_t* kt, const studtable_t* st);

// Выводит таблицу ключей
void print_keytable(const keytable_t* kt);

// Сортирует таблицу ключей
void keytable_sort(keytable_t* kt, sort_t sort_fn);

// Освобождает память
void keytable_destroy(keytable_t* kt);

#endif /* __KEYTABLE_H__ */
