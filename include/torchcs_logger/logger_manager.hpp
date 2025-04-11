#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <filesystem>
#include <fmt/format.h>

#include "log_level.hpp"
#include "logger_options.hpp"

namespace fs = std::filesystem;

class LoggerManager {
private:
    static std::unordered_map<std::string, std::shared_ptr<LoggerManager>> instances;
    static std::mutex instance_mutex;

    std::shared_ptr<spdlog::logger> logger;

    bool is_file_logging = false;
    bool is_console_logging = true;

    fs::path file_logger_directory_path = "logs";

    void Log(LogLevel level, const std::string& message);

    template<typename... Args>
    void Log(LogLevel level, fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(level,fmt::format(fmt_str, std::forward<Args>(args)...));
    }

public:
    static std::shared_ptr<LoggerManager> getInstance(const std::string& name);
    static bool createInstance(const std::string& name);
    static bool deleteInstance(const std::string& name);
    static bool existsInstance(const std::string& name);

    void load_options(LoggerOptions& options);

    void file_logging(bool on);
    void console_logging(bool on);

    void flush_every(std::chrono::seconds interval);
    void flush_on(LogLevel level);

    void info(const std::string& message);
    void verbose(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);
    void debug(const std::string& message);

    template<typename... Args>
    void info(fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(LogLevel::Info,fmt_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void verbose(fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(LogLevel::Verbose,fmt_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(LogLevel::Warn,fmt_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(LogLevel::Error,fmt_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(LogLevel::Critical,fmt_str, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(fmt::format_string<Args...> fmt_str, Args&&... args) {
        Log(LogLevel::Debug,fmt_str, std::forward<Args>(args)...);
    }

    explicit LoggerManager(const std::string& name);
};
