#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "student.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>


bool stud_valid(const student_t* stud)
{
    if (stud == NULL)
        return false;
    
    if (strlen(stud->surname) == 0 ||
        strlen(stud->name) == 0 ||
        strlen(stud->group) == 0)
        return false;
    
    if (stud->gender == UNDEFINED)
        return false;
    
    if (stud->age > 122 || stud->age < 7)
        return false;
    
    if (stud->avg_score < 2 || stud->avg_score > 5)
        return false;

    if (!date_valid(&stud->enroll_date))
        return false;

    if (stud->house == UNKNOWN)
        return false;
    
    if (stud->house == DORM && !dorm_valid(&stud->housing.dorm))
        return false;

    if (stud->house == APPARTMENT && !apt_valid(&stud->housing.appartment))
        return false;

    return true;
}

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

static bool read_uint(uint16_t* num, const char* str)
{
    if (str == NULL)
        return false;

    char* ptr;
    
    *num = strtol(str, &ptr, 10);

    if (*ptr != '\0')
        return false;

    return true;
}

static bool read_double(double* num, const char* str)
{
    if (str == NULL)
        return false;

    char* ptr;
    
    *num = strtod(str, &ptr);

    if (*ptr != '\0')
        return false;

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

    if (status == SUCCESS && !stud_valid(stud))
        status = STUD_ERROR;
        
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

static status_t input_str(const char* prompt, char* dst, size_t dst_size)
{
    status_t status = INPUT_ERROR;
    char* buf = NULL;
    size_t size = 0;

    printf("%s", prompt);
    if (getline(&buf, &size, stdin) >= 0)
    {
        *strchr(buf, '\n') = '\0';
        if (strlen(buf) < dst_size && strlen(buf) > 0)
        {
            strcpy(dst, buf);
            status = SUCCESS;
        }
    }

    free(buf);
    return status;
}

static status_t input_gender(const char* prompt, gender_t* gender)
{
    status_t status = SUCCESS;
    char tmp[MAX_STR] = "";

    status = input_str(prompt, tmp, MAX_STR);
    *gender = str_to_gender(tmp);

    if (*gender == UNDEFINED)
        status = STUD_ERROR;

    return status;
}

static status_t input_uint(const char* prompt, uint16_t* unum)
{
    status_t status = SUCCESS;
    char tmp[MAX_STR] = "";

    char* ptr;

    status = input_str(prompt, tmp, MAX_STR);
    *unum = strtol(tmp, &ptr, 10);

    if (*ptr != '\0')
        status = INPUT_ERROR;

    return status;
}

static status_t input_double(const char* prompt, double* dnum)
{
    status_t status = SUCCESS;
    char tmp[MAX_STR] = "";

    char* ptr;

    status = input_str(prompt, tmp, MAX_STR);
    *dnum = strtod(tmp, &ptr);

    if (*ptr != '\0')
        status = INPUT_ERROR;

    if (*dnum < 2 || *dnum > 5)
        status = STUD_ERROR;

    return status;
}

static status_t input_date(const char* prompt, date_t* date)
{
    status_t status = SUCCESS;
    char tmp[MAX_STR] = "";

    status = input_str(prompt, tmp, MAX_STR);
    *date = str_to_date(tmp);

    if (!date_valid(date))
        status = STUD_ERROR;

    return status;
}

static status_t input_house(const char* prompt, housing_t* house)
{
    status_t status = SUCCESS;
    char tmp[MAX_STR] = "";

    status = input_str(prompt, tmp, MAX_STR);
    *house = str_to_housing(tmp);

    if (*house == UNKNOWN)
        status = STUD_ERROR;

    return status;
}

static status_t input_address(student_t* stud)
{
    status_t status = SUCCESS;

    if (stud->house == DORM)
    {
        status = input_uint("Введите номер общежития [1..10]: ", &stud->housing.dorm.number);

        if (status == SUCCESS)
            status = input_uint("Введите номер комнаты [1..899]: ", &stud->housing.dorm.room);
    }

    if (stud->house == APPARTMENT)
    {
        status = input_str("Введите улицу: ", stud->housing.appartment.street, MAX_STR);

        if (status == SUCCESS)
            status = input_uint("Введите номер дома [1..89]: ", &stud->housing.appartment.house);

        if (status == SUCCESS)
            status = input_uint("Введите квартиру [1..999]: ", &stud->housing.appartment.appt_num);
    }

    return status;
}

status_t input_student(student_t* stud)
{
    status_t status = SUCCESS;

    status = input_str("Введите фамилию студента: ", stud->surname, MAX_STR);

    if (status != SUCCESS)
    {
        printf("Фамилия некорректна.\n");
        return status;
    }

    status = input_str("Введите имя: ", stud->name, MAX_STR);

    if (status != SUCCESS)
    {
        printf("Имя некорректно.\n");
        return status;
    }

    status = input_str("Введите группу: ", stud->group, MAX_STR);

    if (status != SUCCESS)
    {
        printf("Группа некорректна.\n");
        return status;
    }

    status = input_gender("Введите пол (m/f): ", &stud->gender);

    if (status != SUCCESS)
    {
        printf("Пол некорректен.\n");
        return status;
    }

    status = input_uint("Введите возраст: ", &stud->age);

    if (status != SUCCESS || stud->age < 7 || stud->age > 122)
    {
        printf("Возраст некорректен. возраст - [7..122]\n");
        return INPUT_ERROR;
    }
    status = input_double("Введите средний балл: ", &stud->avg_score);

    if (status != SUCCESS)
    {
        printf("Средний балл некорректен. [2..5]\n");
        return status;
    }

    status = input_date("Введите дату поступления (ДД.ММ.ГГГГ): ", &stud->enroll_date);

    if (status != SUCCESS)
    {
        printf("Дата некорректна.\n");
        return status;
    }

    status = input_house("Введите тип жилья (dorm/appartment): ", &stud->house);

    if (status != SUCCESS)
    {
        printf("Тип жилья некорректен.\n");
        return status;
    }

    status = input_address(stud);

    if (status != SUCCESS)
    {
        printf("Информация о месте проживания некорректна.\n");
        return status;
    }

    return status;
}
