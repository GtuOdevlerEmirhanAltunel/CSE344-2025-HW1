#include "commands.h"
#include "logger.h"

int listDir(const char *argv[]) {
  const char *args[] = {"ls", argv[0], 0};
  t_ret ret = runCommands("/bin/ls", args, 0, 0);
  if (ret.stdout) {
    logMessage("%s", ret.stdout);
  }
  return ret.status_code;
}
