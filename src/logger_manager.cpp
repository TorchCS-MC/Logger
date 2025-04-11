#include <torchcs_logger/logger_manager.hpp>
#include <torchcs_logger/custom_formatter.hpp>

#include <spdlog/pattern_formatter.h>

std::string strip_minecraft_colors(const std::string& input) {
    std::string result;
    size_t len = input.length();
    for (size_t i = 0; i < len; ++i) {
        if ((unsigned char)input[i] == 0xC2 && i + 1 < len && (unsigned char)input[i + 1] == 0xA7) {
            i += 2;
        } else {
            result += input[i];
        }
    }
    return result;
}

std::unordered_map<std::string, std::shared_ptr<LoggerManager>> LoggerManager::instances;
std::mutex LoggerManager::instance_mutex;

std::shared_ptr<LoggerManager> LoggerManager::getInstance(const std::string& name) {
    std::lock_guard<std::mutex> lock(instance_mutex);
    auto it = instances.find(name);
    if (it != instances.end()) return it->second;
    return nullptr;
}

bool LoggerManager::createInstance(const std::string& name) {
    std::lock_guard<std::mutex> lock(instance_mutex);
    if (instances.find(name) == instances.end()) {
        instances[name] = std::make_shared<LoggerManager>(name);
        return true;
    }
    return false;
}

bool LoggerManager::deleteInstance(const std::string& name) {
    std::lock_guard<std::mutex> lock(instance_mutex);
    return instances.erase(name) > 0;
}

bool LoggerManager::existsInstance(const std::string& name) {
    std::lock_guard<std::mutex> lock(instance_mutex);
    return instances.find(name) != instances.end();
}

LoggerManager::LoggerManager(const std::string& name) {
    logger = spdlog::stdout_color_mt(name);
    logger->set_level(spdlog::level::trace);
    logger->set_formatter(std::make_unique<CustomFormatter>());
}

void LoggerManager::load_options(LoggerOptions& options) {
    if (!options.getLogPath().empty()) {
        file_logger_directory_path = options.getLogPath();
    }
}

void LoggerManager::Log(LogLevel level, const std::string& message) {
    if (!logger) return;

    if (is_console_logging) {
        spdlog::get(logger->name())->log(static_cast<spdlog::level::level_enum>(level), message);
    }

    std::string file_message = strip_minecraft_colors(message);

    if (is_file_logging) {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;

#ifdef _WIN32
        localtime_s(&tm_buf, &t);
#else
        localtime_r(&t, &tm_buf);
#endif

        char date_buffer[11];
        std::strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d", &tm_buf);

        fs::path log_dir = file_logger_directory_path / logger->name();
        fs::create_directories(log_dir);

        std::string logFilePath = (log_dir / (std::string(date_buffer) + ".txt")).string();

        static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> file_loggers;

        if (file_loggers.find(logFilePath) == file_loggers.end()) {
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, false);
            auto file_logger = std::make_shared<spdlog::logger>(logFilePath, file_sink);
            file_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
            file_loggers[logFilePath] = file_logger;
            spdlog::register_logger(file_logger);
        }

        file_loggers[logFilePath]->log(static_cast<spdlog::level::level_enum>(level), file_message);
        file_loggers[logFilePath]->flush();
    }
}

void LoggerManager::flush_every(std::chrono::seconds interval) {
    spdlog::flush_every(interval);
}

void LoggerManager::flush_on(LogLevel level) {
    logger->flush_on(static_cast<spdlog::level::level_enum>(level));
}

void LoggerManager::console_logging(bool on) {
    is_console_logging = on;
}

void LoggerManager::file_logging(bool on) {
    is_file_logging = on;
}

void LoggerManager::info(const std::string& message) {
    Log(LogLevel::Info, message);
}

void LoggerManager::verbose(const std::string& message) {
    Log(LogLevel::Verbose, message);
}

void LoggerManager::warn(const std::string& message) {
    Log(LogLevel::Warn, message);
}

void LoggerManager::error(const std::string& message) {
    Log(LogLevel::Error, message);
}

void LoggerManager::critical(const std::string& message) {
    Log(LogLevel::Critical, message);
}

void LoggerManager::debug(const std::string& message) {
    Log(LogLevel::Debug, message);
}
