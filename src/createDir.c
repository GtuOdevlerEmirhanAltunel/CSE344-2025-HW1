#include "commands.h"
#include "logger.h"

int createDir(const char *argv[]) {
  const char *args[] = {"mkdir", argv[0], 0};
  t_ret ret = runCommands("/bin/mkdir", args, checkFileFolderExists, argv);
  if (!ret.status_code) {
    logMessage("Directory %s created", argv[0]);
  }
  return ret.status_code;
}
