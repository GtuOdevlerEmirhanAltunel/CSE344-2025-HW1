#ifndef INC_MAIN
#define INC_MAIN

#include <stdlib.h>

#define BUFFER_SIZE 16384

typedef struct {
  int status;
  char message[BUFFER_SIZE];
} result_t;

typedef struct {
  const char *command;
  result_t (*script)(const char *args[]);
  int argc;
} key_value_t;

extern key_value_t command_map[];
extern size_t command_map_size;

void log_msg(const char *str);
result_t run(key_value_t *command, const char *args[]);
int foundCommand(const char *command);

#endif /* INC_MAIN */
