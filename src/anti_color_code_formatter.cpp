#include <torchcs_logger/anti_color_code_formatter.hpp>
#include <spdlog/details/fmt_helper.h>
#include <iostream>

namespace torchcs
{
    void AntiColorCodeFormatter::format(const spdlog::details::log_msg &msg, const std::tm & /*tm*/, spdlog::memory_buf_t &dest) {
        std::string_view log_message(msg.payload.data(), msg.payload.size());

        size_t pos = 0;
        while ((pos = log_message.find("§", pos)) != std::string_view::npos) {
            size_t next_pos = log_message.find("§r", pos);
            if (next_pos != std::string_view::npos) {
                log_message.remove_prefix(next_pos + 2); 
            }
            else {
                break;
            }
        }

        fmt::format_to(std::back_inserter(dest), "{}", log_message);
    }

    std::unique_ptr<spdlog::custom_flag_formatter> AntiColorCodeFormatter::clone() const
    {
        return std::make_unique<AntiColorCodeFormatter>();
    }

}
