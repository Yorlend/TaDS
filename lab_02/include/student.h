#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "misc/appartment.h"
#include "misc/dorm.h"
#include "misc/constants.h"
#include "misc/date.h"
#include "misc/house.h"
#include "misc/gender.h"
#include "misc/status.h"

#define DELIM_CHARS ";"


typedef struct
{
    char surname[MAX_STR];
    char name[MAX_STR];
    char group[MAX_STR];
    gender_t gender;
    uint16_t age;
    double avg_score;
    date_t enroll_date;
    housing_t house;
    union housing
    {
        dorm_t dorm;
        appartment_t appartment;
    } housing;
} student_t;

bool stud_valid(const student_t* stud);

// void stud_write_row(const student_t* stud);
status_t read_student(student_t* stud, const char* str);
status_t read_student_f(student_t* stud, FILE* file);

status_t input_student(student_t* stud);

#endif // _STUDENT_H_