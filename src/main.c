#include "main.h"
#include "functions.h"
#include <string.h>
#include <unistd.h>

key_value_t command_map[] = {
    {"createDir", createDir, 1},
    {"createFile", createFile, 1},
    {"listDir", listDir, 1},
    {"listFilesByExtension", listFilesByExtension, 2},
    {"readFile", readFile, 1},
    {"appendToFile", appendToFile, 2},
    {"deleteDir", deleteDir, 1},
    {"deleteFile", deleteFile, 1},
    {"showLogs", showLogs, 0},
};

size_t command_map_size = sizeof(command_map) / sizeof(key_value_t);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    write(1, "Error: No command provided\nUsage: ./main <command> [args]\n",
          59);
    return 1;
  }

  int command_index = foundCommand(argv[1]);
  if (command_index == -1) {
    write(1, "Error: Command not found\n", 26);
    return 1;
  }

  if (argc - 2 != command_map[command_index].argc) {
    write(1, "Error: Invalid number of arguments\n", 36);
    return 1;
  }

  result_t res = run(&command_map[command_index], (const char **)argv + 2);
  log_msg(res.message);
  write(1, res.message, strlen(res.message));

  return res.status;
}
