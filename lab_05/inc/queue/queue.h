#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "queue_list.h"
#include "queue_arr.h"

/**
 * Реализация очереди:
 * ARRAY_QUEUE - через массив
 * LIST_QUEUE  - через линейный односвязный список
 */
typedef enum 
{
    ARRAY_QUEUE,
    LIST_QUEUE
} qtype_t;


/**
 * @brief Структура очереди
 * 
 */
typedef struct
{
    qtype_t type;       // Реализация очереди
    
    union
    {
        qlist_t lst;    // Очередь на списке
        qarr_t arr;     // Очередь на массиве
    } imp;
    
} queue_t;

/**
 * @brief Создание пустой очереди
 * 
 * \param[in] type тип очереди (ARRAY_QUEUE или LIST_QUEUE)
 * \param[in] size вместимость очереди (для ARRAY_QUEUE)
 * 
 * \return Возвращается очередь: выделенная память под очередь 
 * на массиве или пустая очередь на списке
 */
queue_t queue_create(qtype_t type, uint32_t size);

/**
 * @brief Очищение памяти, занимаемой очередью
 * 
 * @param queue очередь, память из-под которой следует очистить
 */
void queue_destroy(queue_t *queue);

/**
 * @brief Вставка элемента в "хвост" очереди
 * 
 * @param queue очередь, в которую вставляется элемент
 * @param value элемент для вставки
 * @return код ошибки: 0 при успешном завершении.
 */
int queue_push_back(queue_t *queue, request_t value);

/**
 * @brief Вставка элемента в очередь
 * 
 * @param queue очередь, в которую вставляется элемент
 * @param pos позиция для вставки (отсчитывается от головы)
 * @param value элемент для вставки
 * @return код ошибки: 0 при успешном завершении.
 */
int queue_insert(queue_t *queue, uint32_t pos, request_t value);

/**
 * @brief Удаление элемента из "головы" очереди
 * 
 * @param queue очередь, из которой удаляется элемент
 * @param value значение удаляемого элемента
 * @return код ошибки: 0 при успешном завершении.
 */
int queue_pop_front(queue_t *queue, request_t *value);

/**
 * @brief Печатает очередь в stdout
 * 
 * @param queue очередь для печати
 */
void queue_print(const queue_t *queue);

/**
 * @brief Заполняет
 * 
 * @param queue 
 * @param n 
 * @return int 
 */
int queue_fill(queue_t *queue, const int n);

uint32_t queue_size(const queue_t *queue);

#endif /* __QUEUE_H__ */
