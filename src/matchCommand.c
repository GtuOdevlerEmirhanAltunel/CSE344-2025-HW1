#include <stdio.h>

#include "commands.h"
#include "logger.h"

int matchCommand(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <command> <args>\n", argv[0]);
    return 1;
  }

  if (createLogger() != 0) {
    return 1;
  }

  int command = foundCommand(argv[1]);

  if (command == 0) {
    logMessage("Command %s not found", argv[1]);
    return 1;
  }

  if (args_count[command] != argc - 2) {
    logMessage("Command %s requires %d arguments, %d provided", argv[1],
               args_count[command], argc - 2);
    return 1;
  }

  int ret = functions[command](argv + 2);

  closeLogger();
  return ret;
}
