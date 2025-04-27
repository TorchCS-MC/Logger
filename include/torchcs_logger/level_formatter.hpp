#pragma once

#include "interfaces/IFormatter.hpp"

namespace torchcs
{

    class LevelFormatter : public IFormatter
    {
    public:
        void format(const spdlog::details::log_msg &msg, const std::tm &tm_time, spdlog::memory_buf_t &dest) override;
        [[nodiscard]] std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;
    };

}
