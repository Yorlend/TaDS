#ifndef __COMMANDS_H__
#define __COMMANDS_H__

int init_stacks(void);
int opt_output_astack(void);
int opt_output_lstack(void);
int opt_push_low(void);
int opt_push_high(void);
int opt_push_list(void);
int opt_pop_low(void);
int opt_pop_high(void);
int opt_pop_list(void);
int opt_auto_test(void);

int error_handler(void);

#endif /* __COMMANDS_H__ */
