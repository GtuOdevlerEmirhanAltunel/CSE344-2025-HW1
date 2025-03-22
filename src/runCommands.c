#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "commands.h"
#include "logger.h"
#include "utils.h"

t_ret runCommands(const char *commandPath, const char *args[],
                  int (*check_function)(const char *argv[]),
                  const char *argv[]) {
  t_ret ret;
  ret.status_code = 1;
  ret.stdout = 0;
  if (check_function != 0) {
    if (check_function(argv) != 0) {
      return ret;
    }
  }

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    logMessage("Error creating pipe");
    return ret;
  }

  int fork_ret = fork();

  if (fork_ret < 0) {
    logMessage("Error forking");
    close(pipefd[0]);
    close(pipefd[1]);
    return ret;
  }

  if (fork_ret == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], 1);
    dup2(pipefd[1], 2);
    execv(commandPath, (char *const *)args);
    logMessage("Error executing command");
    perror("execl");
    exit(1);
  } else {
    close(pipefd[1]);
    int status;
    waitpid(fork_ret, &status, 0);

    char *stdout = 0;
    char buffer[1024];
    int bytesRead = read(pipefd[0], buffer, sizeof(buffer));
    if (bytesRead > 0) {
      buffer[bytesRead] = '\0';
      char *prev = stdout;
      stdout = string_join(stdout, buffer);
      free(prev);
    }
    close(pipefd[0]);
    ret.status_code = WEXITSTATUS(status);
    ret.stdout = stdout;
    return ret;
  }
}
