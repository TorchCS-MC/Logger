#include <torchcs_logger/level_formatter.hpp>
#include <spdlog/details/fmt_helper.h>
#include <cctype>

namespace torchcs
{
    void LevelFormatter::format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest)
    {
        std::string level = spdlog::level::to_string_view(msg.level).data();
        
        for (auto &c : level)
        {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }

        fmt::format_to(std::back_inserter(dest), "{}", level);
    }

    std::unique_ptr<spdlog::custom_flag_formatter> LevelFormatter::clone() const
    {
        return std::make_unique<LevelFormatter>();
    }

}
