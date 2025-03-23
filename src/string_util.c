#include "string_util.h"
#include <stdlib.h>
#include <string.h>

int string_init(string_t *str) {
  str->str = 0;
  str->len = 0;
  str->capacity = 0;
  return 0;
}

int string_add_str(string_t *str, const char *str2) {
  size_t len = strlen(str2);
  int ret = string_reserve(str, str->len + len + 1);
  if (ret != 0) {
    return ret;
  }
  for (size_t i = 0; i < len; i++) {
    string_add_char(str, str2[i]);
  }
  str->str[str->len] = '\0';
  return 0;
}

int string_add_char(string_t *str, char str2) {
  int ret = string_reserve(str, str->len + 2);
  if (ret != 0) {
    return ret;
  }
  str->str[str->len] = str2;
  str->len++;
  return 0;
}

int string_reserve(string_t *str, size_t len) {
  if (str->capacity >= len) {
    return 0;
  }
  size_t new_capacity = str->capacity == 0 ? 10 : str->capacity * 2;
  if (new_capacity < len) {
    new_capacity = len + 1;
  }
  char *new_str = (char *)calloc(new_capacity, sizeof(char));
  if (new_str == 0) {
    return 1;
  }
  if (str->str != 0) {
    strcpy(new_str, str->str);
    free(str->str);
  }
  str->str = new_str;
  str->capacity = new_capacity;
  return 0;
}

int string_arg_replace(string_t *str, int arg_index, const char *arg) {
  string_t result;
  string_init(&result);
  for (size_t i = 0; i < str->len; i++) {
    if (str->str[i] == '$' && str->str[i + 1] == '0' + arg_index) {
      int ret = string_add_str(&result, arg);
      if (ret != 0) {
        string_free(&result);
        return ret;
      }
      i++;
    } else {
      int ret = string_add_char(&result, str->str[i]);
      if (ret != 0) {
        string_free(&result);
        return ret;
      }
    }
  }
  string_free(str);
  str->str = result.str;
  str->len = result.len;
  str->capacity = result.capacity;
  return 0;
}

int string_free(string_t *str) {
  if (str->str != 0) {
    free(str->str);
    str->str = 0;
  }
  str->len = 0;
  str->capacity = 0;
  return 0;
}
