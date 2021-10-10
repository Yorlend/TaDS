#ifndef __GENDER_H__
#define __GENDER_H__

typedef enum
{
    UNDEFINED,  // Поле для проверки на корректность ввода
    MALE,       // Мужской
    FEMALE      // Женский
} gender_t;

// Переводит строку в пол
gender_t str_to_gender(const char* str);

// Переводит пол в строку
const char* gender_to_str(gender_t gender);

#endif /* __GENDER_H__ */
