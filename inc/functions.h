#ifndef INC_FUNCTIONS
#define INC_FUNCTIONS

#include "main.h"

result_t createDir(const char *args[]);
result_t createFile(const char *args[]);
result_t listDir(const char *args[]);
result_t listFilesByExtension(const char *args[]);
result_t readFile(const char *args[]);
result_t appendToFile(const char *args[]);
result_t deleteDir(const char *args[]);
result_t deleteFile(const char *args[]);
result_t showLogs(const char *args[]);

#endif /* INC_FUNCTIONS */
