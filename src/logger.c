#include "logger.h"

#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static int log_pipe[2];

int createLogger() {
  if (pipe(log_pipe) == -1) {
    perror("pipe");
    return 1;
  }

  int ret = fork();
  if (ret < 0) {
    perror("fork");
    return 1;
  }

  if (ret > 0) {
    close(log_pipe[0]);
    return 0;
  } else {
    close(log_pipe[1]);
    dup2(log_pipe[0], STDIN_FILENO);
    close(log_pipe[0]);

    char buffer[128];

    int file = 0;
    if (access("log.txt", F_OK) != -1) {
      file = open("log.txt", O_WRONLY | O_APPEND);
    } else {
      file = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    ssize_t read_bytes;
    do {
      read_bytes = read(STDIN_FILENO, buffer, sizeof(buffer));
      write(file, buffer, read_bytes);
    } while (read_bytes > 0);

    close(file);
    exit(0);
  }
}

void logMessage(const char *format, ...) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char s[64];
  strftime(s, sizeof(s), "[%x %X]", tm);

  dprintf(log_pipe[1], "%s ", s);
  dprintf(1, "%s ", s);

  va_list args;
  va_start(args, format);
  vdprintf(log_pipe[1], format, args);
  va_end(args);

  va_start(args, format);
  vdprintf(1, format, args);
  va_end(args);
}

void closeLogger() {
  close(log_pipe[1]);
  wait(NULL);
}
