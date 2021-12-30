#include <stdio.h>
#include "misc/errors.h"
#include "misc/timer.h"
#include "tree/tree.h"
#include "hash_table/hash_table.h"
#include "file/file.h"

int prompt_file_name(char *buffer)
{
    printf("Введите имя файла: ");
    if (scanf("%s", buffer) != 1)
        printf("Некорректный ввод.\n");
    else
        return SUCCESS;

    return INP_ERR;
}

int prompt_table_size(size_t *size)
{
    int tmp = 0;

    printf("Введите максимальный размер хеш-таблицы: ");
    if (scanf("%d", &tmp) != 1)
        printf("Вы ввели не число.\n");
    else if (tmp <= 0)
        printf("Максимальный размер должен быть положительным.\n");
    else
    {
        *size = tmp;
        return SUCCESS;
    }
    
    return IO_ERR;
}

int prompt_max_cmp_count(size_t *count)
{
    int tmp = 0;

    printf("Введите максимально допустимое число сравнений в хеш-таблице: ");
    if (scanf("%d", &tmp) != 1)
        printf("Вы ввели не число.\n");
    else if (tmp <= 0)
        printf("Максимально допустимое число сравнений должно быть положительным.\n");
    else
    {
        *count = tmp;
        return SUCCESS;
    }
    
    return IO_ERR;
}

int task_bst_input(node_t **bst, const char *filename)
{
    *bst = bst_input(filename);
    if (*bst == NULL)
    {
        printf("Ошибки при вводе ДДП.\n");
        return IO_ERR;
    }

    return SUCCESS;
}

int task_bst_to_avl(node_t **avl, node_t *bst)
{
    *avl = bst_to_avl(bst);
    if (*avl == NULL)
    {
        printf("Ошибки при создании AVL.\n");
        return MEM_ERR;
    }

    return SUCCESS;
}

int prompt_data_remove(data_t *data)
{
    printf("\nВведите число для удаления: ");
    if (scanf("%d", data) != 1)
    {
        printf("Введено не число.\n");
        return INP_ERR;
    }
    
    printf("\n");
    return SUCCESS;
}

int task_check_data(node_t *tree, data_t data)
{
    size_t cmp = 0;
    const node_t *node = bst_search(tree, data, &cmp);

    if (node == NULL)
    {
        printf("В структурах нет введённого элемента.\n");
        return NO_ELEM;
    }

    return SUCCESS;
}

int task_remove_bst(node_t **tree, data_t value)
{
    size_t cmp = 0;

    TIMER_BEGIN;
    *tree = bst_remove(*tree, value, &cmp);
    TIMER_END;

    printf("Удаление из ДДП дерева: %lld ticks, %zu сравнений.\n", TIMER_TICKS, cmp);
    return SUCCESS;
}

int task_remove_avl(node_t **tree, data_t value)
{
    size_t cmp = 0;

    TIMER_BEGIN;
    *tree = avl_remove(*tree, value, &cmp);
    TIMER_END;

    printf("Удаление из AVL дерева: %lld ticks, %zu сравнений.\n", TIMER_TICKS, cmp);
    return SUCCESS;
}

int task_remove_hash(hash_table_t *table, data_t value, size_t *cmp_count)
{
    TIMER_BEGIN;
    hash_remove(table, value, cmp_count);
    TIMER_END;

    printf("Удаление из хеш-таблицы: %lld ticks, %zu сравнений.\n", TIMER_TICKS, *cmp_count);
    return SUCCESS;
}

int task_remove_file(const char *filename, data_t value)
{
    size_t cmp = 0;

    TIMER_BEGIN;
    f_remove(filename, value, &cmp);
    TIMER_END;

    printf("Удаление из файла: %lld ticks, %zu сравнений.\n", TIMER_TICKS, cmp);
    return SUCCESS;
}

void task_bst_output(const node_t *node, const char *type)
{
    bst_output(node, type);
    printf("Объем занимаемой памяти для %s:         %6zu байт.\n", type, bst_sizeof(node));
    printf("Среднее число сравнений в %s дереве:    %6.1lf\n", type, bst_get_mean_cmp_count(node));
}

void task_hash_output(const hash_table_t *table)
{
    hash_output(table);
    printf("Среднее число сравнений в хеш-таблице:  %6.1lf\n", hash_get_mean_cmp_count(table));
    printf("Объем занимаемой памяти хеш-таблицы:    %6zu байт.\n", hash_sizeof(table));
}

int task_restruct(hash_table_t *table, size_t cmp_count, size_t max_cmp_count)
{
    if (cmp_count <= max_cmp_count)
    {
        printf("Таблица удовлетворяет условию, не реструктуризируем.\n");
        return SUCCESS;
    }

    printf("Реструктуризация хеш-таблицы.\n");
    int status = hash_restruct(table);
    if (status != SUCCESS)
    {
        printf("Ошибки при реструктуризации.\n");
        return status;
    }

    task_hash_output(table);
    size_t mcc = hash_get_max_cmp_count(table);
    printf("Максимальное число сравнений в хеш-таблице: %zu\n", mcc);
    if (mcc <= max_cmp_count)
        printf("Реструктурированная таблица удовлетворяет условию.\n");
    else
        printf("Реструктурированная таблица не удовлетворяет условию.\n");

    return SUCCESS;
}

int main(void)
{
    int status = SUCCESS;
    char filename[256];

    node_t *bst = NULL;
    node_t *avl = NULL;

    hash_table_t table = hash_null();
    size_t table_size = 0;
    size_t cmp_count = 0;
    size_t max_cmp_count = 0;

    data_t data = 0;

    // 0. запрос имени файла
    status = prompt_file_name(filename);

    // 1. строим ДДП
    if (status == SUCCESS)
        status = task_bst_input(&bst, filename);

    // 2. выводим ДДП
    if (status == SUCCESS)
        task_bst_output(bst, "bst");

    // 3. ДДП -> AVL
    if (status == SUCCESS)
        status = task_bst_to_avl(&avl, bst);

    // 4. вывводим AVL
    if (status == SUCCESS)
        task_bst_output(avl, "avl");

    // 5. ввод размера хеш-таблицы
    if (status == SUCCESS)
        status = prompt_table_size(&table_size);

    // 6. ввод макс числа сравнений
    if (status == SUCCESS)
        status = prompt_max_cmp_count(&max_cmp_count);

    // 7. ввод самой хеш-таблицы
    if (status == SUCCESS)
        status = hash_input(&table, table_size, filename);

    // 9. вывод хеш-таблицы
    if (status == SUCCESS)
        task_hash_output(&table);
    
    // вывод размера файла
    if (status == SUCCESS)
        printf("Объем занимаемой памяти в файле: %zu байт.\n", f_sizeof(filename));

    // 10. ввод удаляемого числа
    if (status == SUCCESS)
        status = prompt_data_remove(&data);
    
    if (status == SUCCESS)
        status = task_check_data(avl, data);

    // 11. удаление из ДДП
    if (status == SUCCESS)
        status = task_remove_bst(&bst, data);

    // 11.2. выводим ДДП
    if (status == SUCCESS)
        task_bst_output(bst, "bst");

    // 12. удаление из AVL
    if (status == SUCCESS)
        status = task_remove_avl(&avl, data);

    // 12.2. выводим AVL
    if (status == SUCCESS)
        task_bst_output(avl, "avl");

    // 13. удаление из хеш-таблицы
    if (status == SUCCESS)
        status = task_remove_hash(&table, data, &cmp_count);

    // 13.2. вывод хеш-таблицы
    if (status == SUCCESS)
        task_hash_output(&table);
    
    // 14. удаление из файла
    if (status == SUCCESS)
        status = task_remove_file(filename, data);
    
    if (status == SUCCESS)
        printf("Среднее число сравнений в файле: %.1lf\n", f_get_mean_cmp_count(filename));

    // 8. реструктуризация при необходимости
    if (status == SUCCESS)
        status = task_restruct(&table, cmp_count, max_cmp_count);

    // освобождаем ресурсы
    bst_destroy(bst);
    bst_destroy(avl);
    hash_destroy(&table);

    return status;
}
