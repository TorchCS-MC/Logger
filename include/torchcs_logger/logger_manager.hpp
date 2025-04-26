#pragma once

#include <memory>
#include <filesystem>
#include <chrono>
#include <spdlog/spdlog.h>

#include "custom_formatter.hpp"
#include "log_level.hpp"
#include "logger_options.hpp"

namespace fs = std::filesystem;

class LoggerManager {
private:
    std::shared_ptr<spdlog::logger> logger;
    fs::path file_logger_directory_path = "logs";

public:
    LoggerManager();
    ~LoggerManager();

    void load_options(const LoggerOptions& options);
    void set_flush_interval(std::chrono::seconds interval);
    void set_flush_on_level(LogLevel::Value level);
    void enable_console_logging(bool on);
    void flush();

    void log(LogLevel::Value level, const std::string& area, const std::string& message);

    template<typename... Args>
    void log(LogLevel::Value level, const std::string& area, fmt::format_string<Args...> fmt_str, Args&&... args) {
        log(level, area, fmt::format(fmt_str, std::forward<Args>(args)...));
    }
};
