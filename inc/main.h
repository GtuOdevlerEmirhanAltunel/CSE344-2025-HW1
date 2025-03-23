#ifndef INC_MAIN
#define INC_MAIN

#include <stdlib.h>

typedef struct {
  int status_code;
  const char *stdout;
} result_t;

typedef struct {
  const char *command;
  result_t (*script)(const char *args[]);
  int argc;
} key_value_t;

extern key_value_t command_map[];
extern size_t command_map_size;

void log_msg(const char *str);
result_t run(const char *script);
int foundCommand(const char *command);

#endif /* INC_MAIN */
