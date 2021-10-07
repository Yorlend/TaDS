#include "studtable.h"
#include <stdlib.h>
#include <string.h>


studtable_t stable_empty()
{
    studtable_t table;

    table.data = NULL;
    table.size = 0;

    return table;
}

studtable_t stable_reserve(unsigned int size)
{
    studtable_t table;

    table.data = malloc(size * sizeof(student_t));
    if (table.data != NULL)
        table.size = size;

    return table;
}

void stable_destroy(studtable_t* table)
{
    if (stable_valid(table))
    {
        free(table->data);
        table->data = NULL;
        table->size = 0;
    }
}

bool stable_valid(const studtable_t* table)
{
    return table != NULL && table->data != NULL && table->size > 0;
}

status_t stable_load(studtable_t* table, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        return 1;

    int status = stable_loadf(table, file);
    fclose(file);
    return status;
}

static unsigned int _count_file_lines(FILE* file)
{
    char ch;
    unsigned int lines = 0;

    rewind(file);
    while ((ch = fgetc(file)) != EOF)
        if (ch == '\n')
            lines++;

    rewind(file);
    return lines;
}

status_t stable_loadf(studtable_t* table, FILE* file)
{
    if (file == NULL)
        return FILE_ERROR;
    if (table == NULL)
        return TABLE_ERROR;

    char* line = NULL;
    size_t len = 0;
    (void) line;

    unsigned int size = _count_file_lines(file);
    studtable_t temp = stable_reserve(size);

    status_t status = SUCCESS;

    for (unsigned int i = 0; i < size && status == SUCCESS; i++)
        status = read_student_f(temp.data + i, file);

    if (status == SUCCESS)
        *table = temp;
    else
        stable_destroy(&temp);
    return status;
}

status_t stable_push_back(studtable_t* table, const student_t* stud)
{
    if (!stable_valid(table) || !stud_valid(stud))
        return FUNC_ARGS_ERROR;

    status_t status = MEMORY_ERROR;

    student_t* new_data = realloc(table->data, (table->size + 1) * sizeof(student_t));
    if (new_data)
    {
        table->data = new_data;
        table->data[table->size] = *stud;
        table->size++;
        status = SUCCESS;
    }

    return status;
}

status_t stable_remove(studtable_t* table, size_t id)
{
    if (!stable_valid(table) || id >= table->size)
        return FUNC_ARGS_ERROR;

    while(id < table->size - 1)
    {
        table->data[id] = table->data[id + 1];
        id++;
    }

    table->size--;
    return SUCCESS;
}

static void _stud_row_print(const student_t* stud, size_t id)
{
    printf("\033[32;40m│%4lu│%11s│%8s│%9s│ %1s │ %3d │ %5.2lf │%s│%7s│",
        id, stud->surname, stud->name, stud->group, gender_to_str(stud->gender),
        stud->age, stud->avg_score, date_to_str(&stud->enroll_date),
        housing_to_str(stud->house)
        );
    
    if (stud->house == DORM)
    {
        printf("%5d│%5d│%16s│%5s│%6s│\033[0m\n", stud->housing.dorm.number, stud->housing.dorm.room,
            "-", "-", "-");
    }
    else
    {
        printf("%5s│%5s│", "-", "-");
        if (strlen(stud->housing.appartment.street) <= 16)
            printf("%16s", stud->housing.appartment.street);
        else
        {
            char buf[16];

            strncpy(buf, stud->housing.appartment.street, 14);
            buf[14] = '.';
            buf[15] = '.';
            buf[16] = '\0';

            printf("%16s", buf);
        }
        printf("│%5d│%6d│\033[0m\n", stud->housing.appartment.house, stud->housing.appartment.appt_num);
    }
}

void stable_print(const studtable_t* table)
{
    printf("\033[32;40m╒═id═╤═ surname ═╤═ name ═╤═ group ═╤ g ╤ age ╤ score ╤══ date ══╤ house ╤ Dno.╤ Rno.╤════ street ════╤ Hno.╤ appt.╕\033[0m\n");

    for (size_t i = 0; i < table->size; i++)
        _stud_row_print(table->data + i, i);

    printf("\033[32;40m└────┴───────────┴────────┴─────────┴───┴─────┴───────┴──────────┴───────┴─────┴─────┴────────────────┴─────┴──────┘\033[0m\n");
}
