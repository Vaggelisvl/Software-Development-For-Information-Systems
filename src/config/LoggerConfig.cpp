//
// Created by e.vrailas on 24/10/2023.
//

#include "../../headers/config/LoggerConfig.h"

void LoggerConfig::Init() {
    // Initialize the logger
    spdlog::set_level(spdlog::level::debug);  // Set your desired log level
    s_Logger = spdlog::stdout_logger_mt("my_logger");
}

std::shared_ptr<spdlog::logger>& LoggerConfig::Get() {
    return s_Logger;
}