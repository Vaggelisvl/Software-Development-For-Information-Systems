

#include <ctime>
#include <cstring>
#include <cstdio>
#include "../../headers/config/Logger.h"

bool Logger::loggingEnabled = true;
bool Logger::loggingInfoEnabled = true;
bool Logger::loggingWarnEnabled = true;
bool Logger::loggingErrorEnabled = true;
bool Logger::loggingDebugEnabled = true;
void Logger::Info(const char *message) {
    Log("INFO", message, "\033[32m");  // Green
}

void Logger::Warn(const char *message) {
    Log("WARNING", message, "\033[33m");  // Yellow
}

void Logger::Error(const char *message) {
    Log("ERROR", message, "\033[31m");  // Red
}

void Logger::Log(const char *logLevel, const char *message, const char *color) {
    const char *resetColor = "\x1b[0m"; // ANSI reset color escape code
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now); // Use localtime
    char timestamp[80];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", timeinfo);

    // Print the colored log message
    printf("%s%s %s: %s %s\n", color, timestamp, logLevel, message, resetColor);

}

void Logger::SetLoggingEnabled(bool enabled) {
    loggingEnabled = enabled;
}

bool Logger::IsLoggingEnabled() {
    return loggingEnabled;
}

bool Logger::IsLoggingInfoEnabled() {
    return loggingInfoEnabled;
}

bool Logger::IsLoggingWarnEnabled() {
    return loggingWarnEnabled;
}

bool Logger::IsLoggingErrorEnabled() {
    return loggingErrorEnabled;
}
void Logger::Debug(const char *message) {
    Log("DEBUG", message, "\033[34m");  // Blue
}

bool Logger::IsLoggingDebugEnabled() {
    return loggingDebugEnabled;
}
void Logger::SetSpecificLoggingEnabled( const char *level) {
    if (strcmp(level, "ALL") == 0) {
        loggingInfoEnabled = true;
        loggingErrorEnabled = true;
        loggingWarnEnabled = true;
        loggingDebugEnabled = true;
    } else if (strcmp(level, "NONE") == 0) {
        loggingEnabled = false;
    } else if (strcmp(level, "INFO") == 0) {
        loggingInfoEnabled = true;
        loggingDebugEnabled = false;
        loggingErrorEnabled = false;
        loggingWarnEnabled = false;
    } else if (strcmp(level, "WARN") == 0) {
        loggingWarnEnabled = true;
        loggingDebugEnabled = false;
        loggingErrorEnabled = false;
        loggingInfoEnabled = false;
    } else if (strcmp(level, "ERROR") == 0) {
        loggingErrorEnabled = true;
        loggingDebugEnabled = false;
        loggingInfoEnabled = false;
        loggingWarnEnabled = false;
    } else if (strcmp(level, "DEBUG") == 0) {
        loggingDebugEnabled = true;
        loggingInfoEnabled = false;
        loggingErrorEnabled = false;
        loggingWarnEnabled = false;
    }


}
