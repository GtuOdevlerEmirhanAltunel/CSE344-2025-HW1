#ifndef INC_COMMANDS
#define INC_COMMANDS

extern const int args_count[];
extern int (*functions[])(const char **);
extern const char *commands[];

typedef struct s_ret {
  int status_code;
  char *stdout;
} t_ret;

t_ret runCommands(const char *commandPath, const char *args[],
                  int (*check_function)(const char *argv[]),
                  const char *argv[]);
int foundCommand(const char *command);
int matchCommand(int argc, const char *argv[]);

int checkFileFolderExists(const char *argv[]);

int createDir(const char *argv[]);
int createFile(const char *argv[]);
int listDir(const char *argv[]);

#endif /* INC_COMMANDS */
