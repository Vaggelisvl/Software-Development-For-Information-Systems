//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_LOGGERCONFIG_H
#define PROJECT_2023_1_LOGGERCONFIG_H

#include <memory>


class Logger {
    //TODO implement also the debug
public:
    void Info(const std::string& message);
    void Warn(const std::string& message);
    void Error(const std::string& message);

private:
    void Log(const std::string& logLevel, const std::string& message, const std::string& color);
};
extern Logger log;


#endif //PROJECT_2023_1_LOGGERCONFIG_H
