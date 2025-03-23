#include "main.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void log_msg(const char *str) {
  int fd = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
  if (fd != -1) {
    time_t t = time(0);
    struct tm *tm = localtime(&t);
    char s[64] = {0};
    s[0] = '[';
    s[1] = '0' + tm->tm_mday / 10;
    s[2] = '0' + tm->tm_mday % 10;
    s[3] = '/';
    s[4] = '0' + (tm->tm_mon + 1) / 10;
    s[5] = '0' + (tm->tm_mon + 1) % 10;
    s[6] = '/';
    s[7] = '0' + (tm->tm_year + 1900) / 1000;
    s[8] = '0' + ((tm->tm_year + 1900) % 1000) / 100;
    s[9] = '0' + ((tm->tm_year + 1900) % 100) / 10;
    s[10] = '0' + (tm->tm_year + 1900) % 10;
    s[11] = ' ';
    s[12] = '0' + tm->tm_hour / 10;
    s[13] = '0' + tm->tm_hour % 10;
    s[14] = ':';
    s[15] = '0' + tm->tm_min / 10;
    s[16] = '0' + tm->tm_min % 10;
    s[17] = ':';
    s[18] = '0' + tm->tm_sec / 10;
    s[19] = '0' + tm->tm_sec % 10;
    s[20] = ']';
    s[21] = ' ';
    s[22] = '\0';
    write(fd, s, strlen(s));
    if (str != 0) {
      write(fd, str, strlen(str));
    } else {
      write(fd, "No message provided\n", 20);
    }
    close(fd);
  }
}

result_t run(key_value_t *command, const char *args[]) {
  int pipefd[2];
  result_t res = {0, ""};
  if (pipe(pipefd) == -1) {
    res.status = 1;
    strcpy(res.message, "Error: Pipe failed\n");
    return res;
  }

  pid_t pid = fork();
  if (pid == -1) {
    res.status = 1;
    strcpy(res.message, "Error: Fork failed\n");
    return res;
  }

  if (pid == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    result_t _res = command->script(args);
    write(STDOUT_FILENO, _res.message, strlen(_res.message));
    exit(_res.status);
  } else {
    close(pipefd[1]);
    static char buffer[BUFFER_SIZE];
    size_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';
    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    res.status = WEXITSTATUS(status);
    strncpy(res.message, buffer, BUFFER_SIZE);
    return res;
  }
}

int foundCommand(const char *command) {
  for (size_t i = 0; i < command_map_size; i++) {
    if (strcmp(command, command_map[i].command) == 0) {
      return i;
    }
  }
  return -1;
}
