#include <string.h>

#include "commands.h"

const int args_count[] = {
    0,  // NONE
    1,  // CREATE_DIR,
    1,  // CREATE_FILE,
    1,  // LIST_DIR
};

int (*functions[])(const char **) = {
    0,           // NONE
    createDir,   // CREATE_DIR
    createFile,  // CREATE_FILE
    listDir,     // LIST_DIR
};

const char *commands[] = {"NONE", "createDir", "createFile", "listDir"};

int foundCommand(const char *command) {
  for (unsigned int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
    if (strcmp(command, commands[i]) == 0) {
      return (i);
    }
  }
  return 0;
}
