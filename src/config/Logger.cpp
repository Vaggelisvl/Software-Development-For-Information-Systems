//
// Created by e.vrailas on 24/10/2023.
//


#include <iostream>
#include <ctime>
#include "../../headers/config/Logger.h"

void Logger::Info(const std::string &message) {
    Log("INFO", message, "\033[32m");  // Green
}

void Logger::Warn(const std::string &message) {
    Log("WARNING", message, "\033[33m");  // Yellow
}

void Logger::Error(const std::string &message) {
    Log("ERROR", message, "\033[31m");  // Red
}

void Logger::Log(const std::string &logLevel, const std::string &message, const std::string &color) {
    const std::string resetColor = "\033[0m";
    std::time_t now = std::time(nullptr);
    struct std::tm *timeinfo = std::localtime(&now); // Replace localtime_s with localtime
    char timestamp[80];
    std::strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", timeinfo);

    std::cout << color << timestamp << " " << logLevel << ": " << message << resetColor << std::endl;
}
