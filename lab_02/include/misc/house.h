#ifndef __HOUSE_H__
#define __HOUSE_H__


typedef enum
{
    UNKNOWN,    // Поле для обнаружения ошибок
    DORM,       // Общежитие
    APPARTMENT  // Квартира
} housing_t;

// Перевод из строки в структуру
housing_t str_to_housing(const char* str);

// Перевод из структуры в строку
const char* housing_to_str(housing_t housing);

#endif /* __HOUSE_H__ */
