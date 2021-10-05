#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "student.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>


static bool read_string(char* buf, size_t size, char* src)
{
    if (strlen(src) >= size)
        return false;

    strcpy(buf, src);

    return true;
}

static bool read_gender(gender_t* gender, const char* str)
{
    if (str == NULL)
        return false;

    *gender = str_to_gender(str);
    return true;
}

static bool read_uint(uint8_t* num, const char* str)
{
    if (str == NULL)
        return false;
    
    *num = atoi(str);
    return true;
}

static bool read_double(double* num, const char* str)
{
    if (str == NULL)
        return false;
    
    *num = atof(str);
    return true;
}

static bool read_date(date_t* date,  const char* str)
{
    if (str == NULL)
        return false;
    
    *date = str_to_date(str);
    return true;
}

static bool read_house(housing_t* house, const char* str)
{
    if (str == NULL)
        return false;

    *house = str_to_housing(str);
    return true;
}

static bool read_address(student_t* stud, const char* str)
{
    if (str == NULL)
        return false;

    if (stud->house == DORM)
        stud->housing.dorm = str_to_dorm(str);
        
    else if (stud->house == APPARTMENT)
        stud->housing.appartment = str_to_apt(str);

    return true;
}

void stud_write_row(const student_t* stud)
{
    printf("|%10s|%10s|%s|%s|%u|%.2lf|%s|%10s|",
        stud->surname, stud->name, stud->group,
        gender_to_str(stud->gender), stud->age,
        stud->avg_score, date_to_str(&stud->enroll_date),
        housing_to_str(stud->house));
    
    if (stud->house == DORM)
    {
        printf("||\n");
    }
}

/**
 * Ожидаемый формат ввода:
 * <Фамилия>;<Имя>;<Группа>;<Пол>;<Возраст>;<Средний балл>;<Дата поступления>;<Где проживает>;[...];
 * В зависимости от поля <где проживает> [...]:
 * dorm -> <номер общежития>,<номер комнаты>;
 * appartment -> <улица>,<дом>,<квартира>;
 */
status_t read_student(student_t* stud, const char* str)
{
    status_t status = SUCCESS;
    char* buf = strdup(str);

    if (buf == NULL)
        status = MEMORY_ERROR;
    else
    {
        char* tok = strtok(buf, DELIM_CHARS);

        if (!read_string(stud->surname, MAX_STR, tok))
            status = INPUT_ERROR; // TODO
        
        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_string(stud->name, MAX_STR, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_string(stud->group, MAX_STR, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_gender(&stud->gender, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_uint(&stud->age, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_double(&stud->avg_score, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_date(&stud->enroll_date, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_house(&stud->house, tok))
                status = INPUT_ERROR;
        }

        if (status == SUCCESS)
        {
            tok = strtok(NULL, DELIM_CHARS);
            if (!read_address(stud, tok))
                status = INPUT_ERROR;
        }

        free(buf);
    }

    return status;
}


status_t read_student_f(student_t* stud, FILE* file)
{
    status_t status = FILE_ERROR;
    char* line = NULL;
    size_t size = 0;

    if (getline(&line, &size, file) >= 0)
        status = read_student(stud, line);

    free(line);
    return status;
}