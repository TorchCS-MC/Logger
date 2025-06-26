#include "color_code_formatter.hpp"
#include <torchcs/spdlog/log_color.hpp>

#include <spdlog/details/fmt_helper.h>

namespace torchcs::logger::formatter
{
    void ColorCodeFormatter::format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest)
    {
        std::string message(msg.payload.data(), msg.payload.size());
        std::string formatted_message = color::Type::ColorCodeToFormattedText(message);
        fmt::format_to(std::back_inserter(dest), "{}", formatted_message);
    }
}
