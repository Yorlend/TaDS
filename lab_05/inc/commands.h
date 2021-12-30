#ifndef __COMMANDS_H__
#define __COMMANDS_H__

int init_queues(void);

int opt_run_model(void);
int opt_change_model(void);

int opt_output(void);
int opt_push(void);
int opt_pop(void);

int opt_auto_model(void);
int opt_manual(void);

int error_handler(void);

#endif /* __COMMANDS_H__ */
