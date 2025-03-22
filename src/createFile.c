#include "commands.h"
#include "logger.h"

int createFile(const char *argv[]) {
  const char *args[] = {"touch", argv[0], 0};
  t_ret ret = runCommands("/usr/bin/touch", args, checkFileFolderExists, argv);
  if (!ret.status_code) {
    logMessage("File %s created", argv[0]);
  }
  return ret.status_code;
}
