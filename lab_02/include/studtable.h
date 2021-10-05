#ifndef _AUTOTABLE_H_
#define _AUTOTABLE_H_

#include <stdbool.h>
#include <stdio.h>
#include "student.h"
#include "misc/status.h"


typedef struct
{
    student_t* data;
    unsigned int size;
} studtable_t;

studtable_t stable_empty();
studtable_t stable_reserve(unsigned int size);

void stable_destroy(studtable_t* table);

bool stable_valid(const studtable_t* table);

status_t stable_load(studtable_t* table, const char* filename);
status_t stable_loadf(studtable_t* table, FILE* file);

void stable_print(const studtable_t* table);

#endif // _AUTOTABLE_H_
