//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_LOGGERCONFIG_H
#define PROJECT_2023_1_LOGGERCONFIG_H

#include <spdlog/spdlog.h>

class LoggerConfig {
public:
    static void Init();
    static std::shared_ptr<spdlog::logger>& Get();
};
#define LOG_INFO(...) Logger::Get()->info(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::Get()->debug(__VA_ARGS__)
#define LOG_WARN(...) Logger::Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::Get()->error(__VA_ARGS__)

#endif //PROJECT_2023_1_LOGGERCONFIG_H
