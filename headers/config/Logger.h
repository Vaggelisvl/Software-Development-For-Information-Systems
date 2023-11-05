//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_LOGGERCONFIG_H
#define PROJECT_2023_1_LOGGERCONFIG_H

#include <string>


class Logger {
    //TODO implement also the debug
public:
    static void Info(const char* message);
    static void Warn(const char* message);
    static void Error(const char* message);

    static void SetLoggingEnabled(bool enabled);
    static void SetSpecificLoggingEnabled( const char* level);
    static bool IsLoggingEnabled();
    static bool IsLoggingInfoEnabled();
    static bool IsLoggingWarnEnabled();
    static bool IsLoggingErrorEnabled();
private:
    static void Log(const char* logLevel, const char* message, const char* color);
    // Static flag to control logging
    static bool loggingEnabled;
    static bool loggingInfoEnabled;
    static bool loggingWarnEnabled;

    static bool loggingErrorEnabled;
};
#define LOG_INFO(message) if (Logger::IsLoggingEnabled()&&Logger::IsLoggingInfoEnabled()) Logger::Info(message)
#define LOG_WARN(message) if (Logger::IsLoggingEnabled()&&Logger::IsLoggingWarnEnabled()) Logger::Warn(message)
#define LOG_ERROR(message) if (Logger::IsLoggingEnabled()&&Logger::IsLoggingErrorEnabled) Logger::Error(message)
#define LOG_LEVEL(message) Logger::SetSpecificLoggingEnabled(message)


#endif //PROJECT_2023_1_LOGGERCONFIG_H
