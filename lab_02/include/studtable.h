#ifndef _AUTOTABLE_H_
#define _AUTOTABLE_H_

#include <stdbool.h>
#include <stdio.h>
#include "student.h"
#include "misc/status.h"
#include "keytable.h"
#include "misc/sort.h"


typedef struct studtable
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

status_t stable_push_back(studtable_t* table, const student_t* stud);
status_t stable_remove(studtable_t* table, size_t id);

void stable_print(const studtable_t* table);
void stable_cond_print(studtable_t* table, uint16_t year);
void stable_print_key(const studtable_t* table, const keytable_t* kt);

void stable_sort(studtable_t* table, sort_t sort_fn);


#endif // _AUTOTABLE_H_
