#pragma once

#include "interfaces/IFormatter.hpp"

namespace torchcs::logger::formatter
{

    class ColorCodeFormatter : public logger::interfaces::IFormatter
    {
    public:
        void format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest) override;

        [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override
        {
            return std::make_unique<ColorCodeFormatter>();
        }
    };
}