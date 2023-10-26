//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_LOGGERCONFIG_H
#define PROJECT_2023_1_LOGGERCONFIG_H

#include <string>


class Logger {
    //TODO implement also the debug
public:
    static void Info(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);
private:
    static void Log(const std::string& logLevel, const std::string& message, const std::string& color);
};
#define LOG_INFO(message) Logger::Info(message)
#define LOG_WARN(message) Logger::Warn(message)
#define LOG_ERROR(message) Logger::Error(message)

#endif //PROJECT_2023_1_LOGGERCONFIG_H
