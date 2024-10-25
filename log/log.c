#include "log.h"

#include <stdarg.h>
#include <stdio.h>

/** @private
 * Log a message with a specified log level to the given output stream.
 *
 * @param stream The output stream where the log message will be printed (e.g., `stdout` or `stderr`).
 * @param level The log level (e.g., `"ERROR"`, `"INFO"`, `"DEBUG"`).
 * @param format The format string for the log message.
 * @param args Variable arguments to format and log.
 */
static void _log_message(FILE *stream, const char *level, const char *format, va_list args) {
    fprintf(stream, "[%s] ", level);
    vfprintf(stream, format, args);
    fprintf(stream, "\n");
}

void log_message(FILE *stream, const char *level, const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_message(stream, level, format, args);
    va_end(args);
}

void log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_message(stderr, "ERROR", format, args);
    va_end(args);
}

void log_info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_message(stdout, "INFO", format, args);
    va_end(args);
}

void log_debug(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _log_message(stdout, "DEBUG", format, args);
    va_end(args);
}
