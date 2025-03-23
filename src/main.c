#include "main.h"
#include "functions.h"
#include "string_util.h"
#include <string.h>
#include <unistd.h>

key_value_t command_map[] = {
    {"createDir", createDir, 1},
};

size_t command_map_size = sizeof(command_map) / sizeof(key_value_t);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    write(1, "Error: No command provided\n", 28);
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

  string_t result;
  string_init(&result);
  string_add_str(&result, command_map[command_index].script);
  for (int i = 0; i < command_map[command_index].argc; i++) {
    string_arg_replace(&result, i, argv[i + 2]);
  }

  result_t res = run(result.str);
  string_free(&result);
  log_msg(res.stdout);
  write(1, res.stdout, strlen(res.stdout));

  return res.status_code;
}
