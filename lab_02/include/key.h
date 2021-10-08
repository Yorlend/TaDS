#ifndef _KEY_H_
#define _KEY_H_

#include <stddef.h>
#include "student.h"


typedef struct key
{
    size_t id;
    double avg;
} _key_t;

_key_t stud_to_key(const student_t* stud, size_t id);

#endif // _KEY_H_