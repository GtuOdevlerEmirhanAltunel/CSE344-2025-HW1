#ifndef LOGGER
#define LOGGER

int createLogger();
void logMessage(const char *format, ...);
void closeLogger();

#endif /* LOGGER */
