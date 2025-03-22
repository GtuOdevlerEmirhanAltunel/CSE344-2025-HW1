#include "commands.h"
#include "logger.h"

int checkFileFolderExists(const char *argv[]) {
  const char *args[] = {"stat", argv[0], 0};
  t_ret ret = runCommands("/bin/stat", args, 0, 0);
  if (!ret.status_code) {
    logMessage("File/Folder %s already exists, cannot create.", argv[0]);
    return 1;
  }
  return 0;
}
