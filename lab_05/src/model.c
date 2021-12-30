#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils/errors.h"
#include "model.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct
{
    queue_t queue_lst;
    queue_t queue_arr;

    model_result_t results;

    // прошедшее время с момента начала моделирования
    double curr_time;

    // сколько времени осталось до реализации следующих событий
    double request_time; // приход заявки 1го типа
    double oa_time;      // окончание обработки заявки в ОА

    // текущая обрабатываемая ОА заявка
    request_t dispatching_request;
} model_t;

static model_t model;

params_t model_default_params(void)
{
    params_t params;

    params.t1.min = 0.0;
    params.t1.max = 5.0;
    params.t2.min = 0.0;
    params.t2.max = 4.0;
    params.t3.min = 0.0;
    params.t3.max = 4.0;

    return params;
}

static void _model_results_reset(model_result_t* results)
{
    results->status = SUCCESS;
    results->total_time = 0.0;
    results->push_time = 0.0;
    results->dispatch_time = 0.0;
    results->requests_processed = 0;
    results->request2_cycles = 0;

    results->queue_size = 0;
    results->avg_qsize_enumerator = 0.0;
    results->avg_qsize_denominator = 0.0;

    results->requests_entered = 0;
    results->requests_leaved = 0;

    results->average_wait_time = 0.0;
    results->oa_downtime = 0.0;
}

int model_reset(size_t capacity)
{
    queue_destroy(&model.queue_arr);
    queue_destroy(&model.queue_lst);
    _model_results_reset(&model.results);

    model.queue_arr = queue_create(LIST_QUEUE, capacity);
    model.queue_lst = queue_create(LIST_QUEUE, capacity);

    model.curr_time = 0.0;
    model.request_time = 0.0;
    model.oa_time = 0.0;

    return model.queue_arr.imp.arr.capacity == 0 ? MEM_ERR : SUCCESS;
}

void print_results(model_result_t result, size_t requests_count)
{
    printf("Результаты моделирования после обработки %ld заявок:\n", requests_count + 1);
    printf("Время прихода: %.2lf е.в.\n", result.push_time);
    printf("Время обслуживания: %.2lf е.в.\n", result.dispatch_time);
    printf("Кол-во обработанных заявок: %lu\n", result.requests_processed);
    printf("Кол-во обращений заявки 2го типа: %lu\n", result.request2_cycles);
    printf("Время простоя %.2lf е.в.\n", result.push_time - result.dispatch_time);
    printf("Общее время моделирования: %.2lf е.в.\n", result.total_time);
}

static inline double _random_time(time_intv_t interval)
{
    const int resolution = 1001;
    return interval.min + (rand() % resolution) * (interval.max - interval.min) / (resolution - 1);
}

// Отправка новой заявки для обработки в хвост очереди.
// Здесь уместно фиксировать реальное время обработки очередей
static int _model_send_request(model_t *model, request_t request)
{
    int status = queue_push_back(&model->queue_arr, request);
    if (status == SUCCESS)
        status = queue_push_back(&model->queue_lst, request);
    return status;
}

// Извлечение заявки из головы очереди.
// Здесь уместно фиксировать реальное время обработки очередей
static bool _model_receive_request(model_t *model, request_t *request)
{
    int status = queue_pop_front(&model->queue_arr, request);
    if (status == SUCCESS)
        status = queue_pop_front(&model->queue_lst, request);
    return status == SUCCESS;
}

// вставляет заявку не далее 4 позиции с головы
static int _model_insert_request(model_t *model, request_t request)
{
    uint32_t pos = rand() % 4;
    int status = queue_insert(&model->queue_arr, pos, request);
    if (status == SUCCESS)
        status = queue_insert(&model->queue_lst, pos, request);
    return status;
}

model_result_t model_run(size_t requests_amount, params_t params)
{
    if (model.curr_time == 0.0)
    {
        model.dispatching_request = (request_t){ .id = 0, .type = 2 };
        model.oa_time = _random_time(params.t3);
        model.request_time = _random_time(params.t1);
    }

    int eps_printed = 0;

    int in_tasks = 0;
    // int out_tasks = 0;
    // int calls = 0;
    // int calls_1 = 1;
    // int c1_counter = 0;
 
    // int overall_len = 0;

    int status;
    for (size_t reqs = 1; reqs <= requests_amount;)
    {
        /* Алгоритм работы моделирования:
            1. Выбрать ближайшее событие (по времени) из следующих:
                1.1. Приход заявки 1го типа
                1.2. Завершение обработки текущей заявки аппаратом
            2. Реализовать выбранное событие
            3. Увеличить счётчик времени
            4. Уменьшить времена next_request_1_time и oa_time
            5. Рассчитать новое время до следующего события того же типа
        */

        if (model.request_time < model.oa_time || model.oa_time < 0.0) // если новая заявка пришла раньше, чем обработалась текущая
        {
            double time_delta = model.request_time;

            status = _model_send_request(&model, (request_t){ .id = reqs, .type = 1 });
            if (status != SUCCESS)
                break;

            model.request_time = _random_time(params.t1); // Расчёт нового времени до следующего события того же типа
            model.oa_time -= time_delta;
            model.curr_time += time_delta;

            if (in_tasks < requests_amount)
            {
                model.results.push_time += model.request_time;
                in_tasks++;
            }
        }
        else // если текущая заявка обработалась раньше, чем пришла новая
        {
            double time_delta = model.oa_time;

            // Запустить заявку снова в очередь, если она 2го типа
            if (model.dispatching_request.type == 2)
            {
                status = _model_insert_request(&model, model.dispatching_request);
                if (status != SUCCESS)
                    break;

                model.results.request2_cycles++;
            }
            
            if (_model_receive_request(&model, &model.dispatching_request))
            {
                // Действительно взяли заявку на обслуживание
                bool type1 = model.dispatching_request.type == 1;
                model.oa_time = _random_time(type1 ? params.t2 : params.t3);
                if (type1)
                    model.results.dispatch_time += model.oa_time;
                
                // Увеличиваем счётчик заявок
                if ((reqs + 1) % 100 == 0)
                {
                    model.results.status = status;
                    model.results.total_time = model.curr_time;
                    model.results.requests_processed = requests_amount + model.results.request2_cycles;
                    model.results.queue_size = model.queue_arr.imp.arr.size;
                    print_results(model.results, reqs);
                }
                
                if (type1 || reqs == 999)
                    reqs++;

                if (reqs == 1000 && !eps_printed)
                {
                    eps_printed = 1;

                    double in_exp = (params.t1.max + params.t1.min) / 2 * (model.results.requests_processed - model.results.request2_cycles);
                    double in_exp_eps = abs(model.results.push_time - in_exp) / MAX(model.results.push_time, in_exp) * 100;

                    double out_exp = (params.t2.max + params.t2.min) / 2 * (model.results.requests_processed - model.results.request2_cycles);
                    double out_exp_eps = abs(model.results.dispatch_time - out_exp) / MAX(model.results.dispatch_time, out_exp) * 100;
                
                    printf("Ожидаемое время прихода -- %.2lf е.в., погрешность -- %.2lf%%\n", in_exp, in_exp_eps);
                    printf("Ожидаемое время обслуживания: %.2lf е.в., погрешность -- %.2lf%%\n", out_exp, out_exp_eps);
                }
            }
            else
            {
                // Очередь пуста - обслуживающий аппарат простаивает
                model.oa_time = -1.0;
            }

            model.request_time -= time_delta;
            model.curr_time += time_delta;
        }
    }

    model.results.status = status;
    model.results.total_time = model.curr_time;
    model.results.requests_processed = requests_amount + model.results.request2_cycles;
    model.results.queue_size = model.queue_arr.imp.arr.size;
    return model.results;
}
