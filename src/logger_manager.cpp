#include <torchcs_logger/logger_manager.hpp>
#include <spdlog/sinks/basic_file_sink.h>  
#include <spdlog/sinks/stdout_color_sinks.h>
#include <torchcs_logger/custom_file_formatter.hpp>

LoggerManager::LoggerManager() {
    logger = spdlog::stdout_color_mt("torchcs");
    logger->set_level(spdlog::level::trace);
    logger->set_formatter(std::make_unique<CustomFormatter>());
}

LoggerManager::~LoggerManager() {
    spdlog::drop("torchcs");
}

void LoggerManager::load_options(const LoggerOptions& options) {

    if (!options.getLogPath().empty()) {
        file_logger_directory_path = options.getLogPath();

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

        fs::path file_path = file_logger_directory_path / (std::string(date_buffer) + ".txt");

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path.string(), true);
        file_sink->set_formatter(std::make_unique<CustomFileFormatter>());

        logger->sinks().push_back(file_sink);
    }
}

void LoggerManager::enable_console_logging(bool on) {
    if (on) {
        logger->set_level(spdlog::level::trace);
    } else {
        logger->set_level(spdlog::level::off);
    }
}

void LoggerManager::set_flush_interval(std::chrono::seconds interval) {
    spdlog::flush_every(interval);
}

void LoggerManager::set_flush_on_level(LogLevel::Value level) {
    logger->flush_on(static_cast<spdlog::level::level_enum>(level));
}

void LoggerManager::flush() {
    logger->flush();
}

void LoggerManager::log(LogLevel::Value level, const std::string& area, const std::string& message) {
    logger->log(static_cast<spdlog::level::level_enum>(level), "[{}] {}", area, message);
}
