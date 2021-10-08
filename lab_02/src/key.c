#include "key.h"

_key_t stud_to_key(const student_t* stud, size_t id)
{
    _key_t key = { 0 };

    if (stud_valid(stud))
    {
        key.id = id;
        key.avg = stud->avg_score;
    }

    return key;
}
