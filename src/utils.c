#include <stdlib.h>
#include <string.h>

char *string_join(const char *s1, const char *s2) {
  size_t size1 = s1 ? strlen(s1) : 0;
  size_t size2 = s2 ? strlen(s2) : 0;

  char *out = (char *)malloc(size1 + size2 + 1);
  if (!out) return 0;
  size_t i = 0;

  for (size_t j = 0; j < size1; i++, j++) {
    out[i] = s1[j];
  }

  for (size_t j = 0; j < size2; i++, j++) {
    out[i] = s2[j];
  }

  return out;
}
