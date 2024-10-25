#pragma once

#include <stdio.h>

/**
 * Log a message with a specified log level to the given output stream.
 *
 * @param stream The output stream where the log message will be printed (e.g., stdout or stderr).
 * @param level The log level (e.g., `"ERROR"`, `"INFO"`, `"DEBUG"`).
 * @param format The format string for the log message.
 * @param ... Variable arguments to format and log.
 */
void log_message(FILE *stream, const char *level, const char *format, ...);

/**
 * Log an error message.
 *
 * @param format The format string for the error message.
 * @param ... Variable arguments to format and log.
 */
void log_error(const char *format, ...);

/**
 * Log an informational message.
 *
 * @param format The format string for the informational message.
 * @param ... Variable arguments to format and log.
 */
void log_info(const char *format, ...);

/**
 * @brief Log a debug message.
 *
 * @param format The format string for the debug message.
 * @param ... Variable arguments to format and log.
 */
void log_debug(const char *format, ...);
