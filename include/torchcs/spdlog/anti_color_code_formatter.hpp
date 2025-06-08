#pragma once

#include "interfaces/IFormatter.hpp"

namespace torchcs
{

    class AntiColorCodeFormatter : public IFormatter
    {
    public:
        void format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest) override;

        [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override;
    };
}