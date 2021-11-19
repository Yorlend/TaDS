#ifndef __MEMTRACK_H__
#define __MEMTRACK_H__

// Состояние адресов памяти
typedef enum
{
    UNUSED,     // Неиспользован
    USED,       // Использован
    REUSED      // Переиспользован
} memstate_t;

typedef void (*addr_printer_t)(const void*, memstate_t state);

// инициализация
void memtrack_init(void);

// очистка памяти
void memtrack_clean(void);

void memtrack_toggle_addr(const void *addr, memstate_t state);

void memtrack_print(addr_printer_t printer);

#endif /* __MEMTRACK_H__ */
