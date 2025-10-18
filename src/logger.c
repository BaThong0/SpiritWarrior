#include "../include/logger.h"

static FILE *log_file = NULL;
static LogLevel current_level = LOG_LEVEL_DEBUG;

/* Initialize logger */
void log_init(const char *filename, LogLevel level)
{
    current_level = level;
    if(filename != NULL)
    {
        log_file = fopen(filename, "a");
        if(log_file == NULL)
        {
            fprintf(stderr, "[LOGGER] Failed to open log file: %s\n", filename);
            log_file = stderr;
        }
    }
    else 
    {
        log_file = stderr;
    }
}

/* Core log function */
void log_message(LogLevel level, const char *file, int line, const char *func, const char *fmt, ...)
{
    if(level < current_level || level >= LOG_LEVEL_NONE)
    {
        printf("There is no log at this level\n");
    }
    if(!log_file)
    {
        log_file = stderr;
    }
    /* Timestamp */
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_buf[20];
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);

    /* Level string */
    const char *level_str[] = { "DEBUG", "INFO", "WARN", "ERROR" };
    
    /* Print prefix (with function name ) */
    fprintf(log_file, "[%s] [%s] (%s:%d %s)", time_buf, level_str[level], file, line, func);

    /* Variadic print */
    va_list args;
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);
}