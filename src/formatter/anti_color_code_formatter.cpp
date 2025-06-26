#include "anti_color_code_formatter.hpp"

#include <torchcs/spdlog/log_color.hpp>
#include <spdlog/details/fmt_helper.h>
#include <iostream>

namespace torchcs::logger::formatter
{
    void AntiColorCodeFormatter::format(const spdlog::details::log_msg &msg, const std::tm & /*tm*/, spdlog::memory_buf_t &dest) {
        
        std::string_view log_message(msg.payload.data(), msg.payload.size());

        std::string clean_message = color::Type::RemoveAllColorCodeFromText(std::string(log_message));

        fmt::format_to(std::back_inserter(dest), "{}", clean_message);
    }

    std::unique_ptr<spdlog::custom_flag_formatter> AntiColorCodeFormatter::clone() const
    {
        return std::make_unique<AntiColorCodeFormatter>();
    }

}
