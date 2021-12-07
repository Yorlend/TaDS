#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "misc/types.h"
#include <stdbool.h>
#include <stddef.h>

#define DEFAULT_STEP 1
#define DEFAULT_FUNC hasher1


typedef size_t (*hf_t)(data_t, size_t);

typedef struct
{
    data_t key;
    bool has_value;
    size_t cmp_count;
} hash_data_t;

typedef struct
{
    size_t size;
    size_t step;
    hash_data_t *data;
    hf_t func;
} hash_table_t;

/**
 * @brief Нулевая хеш-таблица
 * 
 * @return hash_table_t 
 */
hash_table_t hash_null(void);

/**
 * @brief Выделение памяти под хеш-таблицу
 * 
 * @param size размер хеш-таблицы
 * @param step шаг для устранения коллизий
 * @param func хеш-функция
 * @return hash_table_t 
 */
hash_table_t hash_init(size_t size, size_t step, hf_t func);

/**
 * @brief Освобождение памяти из-под хеш-таблицы
 * 
 * @param table хеш-таблица
 */
void hash_destroy(hash_table_t *table);

/**
 * @brief Ввод хеш-таблицы
 * 
 * @param table хеш-таблицы
 * @param size максимальный размер хеш-таблицы
 * @param filename имя входного файла
 * @return int 
 */
int hash_input(hash_table_t *table, size_t size, const char *filename);

/**
 * @brief Вывод хеш-таблицы
 * 
 * @param table хеш-таблица
 */
void hash_output(const hash_table_t *table);

/**
 * @brief Поиск в хеш-таблице
 * 
 * @param table хеш-таблица
 * @param data искомый ключ
 * @return true 
 * @return false 
 */
bool hash_find(hash_table_t *table, data_t data);

/**
 * @brief Вставка в хеш-таблицу
 * 
 * @param table хеш-таблица
 * @param data ключ
 * @return int 
 */
int hash_insert(hash_table_t *table, data_t data);

/**
 * @brief Удаление из хеш-таблицы
 * 
 * @param table хеш-таблица
 * @param data удаляемый ключ
 * @param cmp_count максимальное число сравнений
 * @return int 
 */
int hash_remove(hash_table_t *table, data_t data, size_t *cmp_count);

/**
 * @brief Вычисление среднего числа сравнений
 * 
 * @param table хеш-таблица
 * @return double 
 */
double hash_get_mean_cmp_count(const hash_table_t *table);

/**
 * @brief Вычисление максимального числа сравнений
 * 
 * @param table хеш-таблица
 * @return size_t 
 */
size_t hash_get_max_cmp_count(const hash_table_t *table);

/**
 * @brief Размер занимаемый под хеш-таблицу памяти
 * 
 * @param table хеш-таблица
 * @return size_t 
 */
size_t hash_sizeof(const hash_table_t *table);

/**
 * @brief Реструктуризация хеш-таблицы
 * 
 * @param table хеш-таблица
 * @return int 
 */
int hash_restruct(hash_table_t *table);

/**
 * @brief Хеш-функция на основе деления
 * 
 * @param data данные, подлежащие хешированию
 * @param table_size размер хеш-таблицы
 * @return size_t 
 */
size_t hasher1(data_t data, size_t table_size);

/**
 * @brief Хеш-функция на основе хеширования Фиббоначи (мультипликативная форма)
 * 
 * @param data данные, подлежащие хешированию
 * @param table_size размер хеш-таблицы
 * @return size_t 
 */
size_t hasher2(data_t data, size_t table_size);

#endif /* __HASH_TABLE_H__ */
