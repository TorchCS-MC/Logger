#pragma once

#include "interfaces/IFormatter.hpp"

namespace torchcs::logger::formatter
{

    class LevelFormatter : public logger::interfaces::IFormatter
    {
    public:
        void format(const spdlog::details::log_msg &msg, const std::tm &tm_time, spdlog::memory_buf_t &dest) override;
        [[nodiscard]] std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;
    };

}
