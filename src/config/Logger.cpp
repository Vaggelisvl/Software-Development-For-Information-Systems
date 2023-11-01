//
// Created by e.vrailas on 24/10/2023.
//


#include <ctime>
#include "../../headers/config/Logger.h"

void Logger::Info(const char* message) {
    Log("INFO", message, "\033[32m");  // Green
}

void Logger::Warn(const char* message) {
    Log("WARNING", message, "\033[33m");  // Yellow
}

void Logger::Error(const char* message) {
    Log("ERROR", message, "\033[31m");  // Red
}

void Logger::Log(const char* logLevel, const char* message, const char* color) {
    const char* resetColor = "\x1b[0m"; // ANSI reset color escape code
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now); // Use localtime
    char timestamp[80];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", timeinfo);

    // Print the colored log message
    printf("%s%s %s: %s %s\n", color, timestamp, logLevel, message, resetColor);

}
