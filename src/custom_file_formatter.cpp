
#include <torchcs_logger/custom_file_formatter.hpp>

#include <fmt/format.h>

void CustomFileFormatter::format(const spdlog::details::log_msg& msg, spdlog::memory_buf_t& dest) {
    auto t = std::chrono::system_clock::to_time_t(msg.time);
    std::tm tm_buf;

#ifdef _WIN32
    localtime_s(&tm_buf, &t);
#else
    localtime_r(&t, &tm_buf);
#endif

    char time_buffer[20];
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &tm_buf);

    std::string log_level;
    switch (msg.level) {
        case spdlog::level::info:     
            log_level = "INFO";     
            break;
        case spdlog::level::warn:     
            log_level = "WARN";     
            break;
        case spdlog::level::err:      
            log_level = "ERROR";    
            break;
        case spdlog::level::debug:    
            log_level = "DEBUG";    
            break;
        case spdlog::level::critical: 
            log_level = "CRITICAL"; 
            break;
        case spdlog::level::trace:    
            log_level = "TRACE";    
            break;
        default:
            log_level = "UNKNOWN";  
        break;
    }

    std::string formatted_message = fmt::to_string(msg.payload);

    fmt::format_to(
        std::back_inserter(dest),
        "[{}] [{}] {}\n",
        time_buffer, log_level, formatted_message
    );
}

std::unique_ptr<spdlog::formatter> CustomFileFormatter::clone() const {
    return std::make_unique<CustomFileFormatter>();
}