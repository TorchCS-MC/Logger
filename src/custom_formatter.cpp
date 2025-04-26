#include <torchcs_logger/custom_formatter.hpp>
#include <torchcs_logger/log_color.hpp>

const std::unordered_map<char, std::string> MC_COLORS = {
        {'0', "\033[30m"},
        {'1', "\033[34m"},
        {'2', "\033[32m"},
        {'3', "\033[36m"},
        {'4', "\033[31m"},
        {'5', "\033[35m"},
        {'6', "\033[38;2;255;140;0m"},
        {'7', "\033[37m"},
        {'8', "\033[90m"},
        {'9', "\033[94m"},
        {'a', "\033[92m"},
        {'b', "\033[96m"},
        {'c', "\033[91m"},
        {'d', "\033[95m"},
        {'e', "\033[93m"},
        {'f', "\033[97m"},
        {'l', "\033[1m"},
        {'r', "\033[0m"}
};

std::string CustomFormatter::convert_minecraft_colors(const std::string& input) {

    std::string result;
    size_t len = input.length();

    for (size_t i = 0; i < len; ++i) {
        if ((unsigned char)input[i] == 0xC2 && i + 1 < len && (unsigned char)input[i + 1] == 0xA7) {
            i++;
            char color_code = input[i + 1];

            if (MC_COLORS.count(color_code)) {
                result += MC_COLORS.at(color_code);
                i++;
            }
        }
        else {
            result += input[i];
        }
    }

    return result + "\033[0m";
}


void CustomFormatter::format(const spdlog::details::log_msg& msg, spdlog::memory_buf_t& dest) {
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
    std::string color;

    switch (msg.level) {
        case spdlog::level::info:
            log_level = "INFO"; 
            color = "\033[97m";
            break;
        case spdlog::level::warn:
            log_level = "WARN"; 
            color = "\033[38;2;255;140;0m";
            break;
        case spdlog::level::err:
            log_level = "ERROR"; 
            color = "\033[91m";
            break;
        case spdlog::level::debug:
            log_level = "DEBUG"; 
            color = "\033[97m";
            break;
        case spdlog::level::critical:
            log_level = "CRITICAL";
            color = "\033[97m";
             break;
        case spdlog::level::trace:
            log_level = "TRACE"; 
            color = "\033[97m";
            break;
        default:
            log_level = "UNKNOWN";
            color = "\033[91m";
            break;
    }

    std::string formatted_message = convert_minecraft_colors(fmt::to_string(msg.payload));
    fmt::format_to(std::back_inserter(dest), "{}[{}] [{}] {}{}\n", color, time_buffer, log_level, formatted_message, "\033[97m");
}

std::unique_ptr<spdlog::formatter> CustomFormatter::clone() const {
    return std::make_unique<CustomFormatter>();
}
