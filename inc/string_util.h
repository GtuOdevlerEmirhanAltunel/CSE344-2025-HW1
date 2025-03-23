#ifndef INC_STRING_UTIL
#define INC_STRING_UTIL

#include <stdlib.h>

typedef struct {
  char *str;
  size_t len;
  size_t capacity;
} string_t;

int string_init(string_t *str);
int string_add_str(string_t *str, const char *str2);
int string_add_char(string_t *str, char str2);
int string_reserve(string_t *str, size_t len);
int string_arg_replace(string_t *str, int arg_index, const char *arg);
int string_free(string_t *str);

#endif /* INC_STRING_UTIL */
