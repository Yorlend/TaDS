#ifndef __KEY_H__
#define __KEY_H__

#include <stddef.h>
#include "student.h"


typedef struct key
{
    size_t id;
    double avg;
} _key_t;

_key_t stud_to_key(const student_t* stud, size_t id);

#endif /* __KEY_H__ */
