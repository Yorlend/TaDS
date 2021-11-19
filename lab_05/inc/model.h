#ifndef __MODEL_H__
#define __MODEL_H__

#include "utils/types.h"
#include "queue/queue.h"
#include <stddef.h>

/**
 * @brief Структура с параметрами моделирования
 */
typedef struct
{
    time_intv_t t1;
    time_intv_t t2;
    time_intv_t t3;
} params_t;

/**
 * @brief Структура с результатами моделирования
 */
typedef struct
{
    int status;
    double total_time;
    double push_time;
    double dispatch_time;
    size_t requests_processed;
    size_t request2_cycles;

    size_t queue_size;
    double avg_qsize_enumerator;
    double avg_qsize_denominator;
    size_t requests_entered;
    size_t requests_leaved;

    double average_wait_time;
    double oa_downtime;
} model_result_t;

/**
 * @brief Временные настройки по-умолчанию
 * 
 * @return структура с параметрами
 */
params_t model_default_params(void);

/**
 * @brief Сбрасывает состояние моделируемого аппарата.
 * Очищает очередь, сбрасывает накопленные данные
 *
 * @param capacity - вместимость рабочей очереди
 * @return SUCCESS - успешная инициализация модели,
 *          MEM_ERR - ошибка при выделении памяти.
 */
int model_reset(size_t capacity);

void print_results(model_result_t result, size_t requests_count);

/**
 * @brief Моделирование работы обслуживающего аппарата
 *
 * @param requests_amount - число заявок 1го типа, которые требуется обслужить
 * @param params - параметры моделирования
 * @return структура с результатами моделирования
 */
model_result_t model_run(size_t requests_amount, params_t params);

#endif /* __MODEL_H__ */
