#pragma once

#include <spdlog/details/log_msg.h>
#include <spdlog/common.h>
#include <spdlog/pattern_formatter.h>

#include <memory>

namespace torchcs
{

    class IFormatter : public spdlog::custom_flag_formatter
    {
    public:
        virtual ~IFormatter() = default;

        virtual void format(const spdlog::details::log_msg &msg, const std::tm &time, spdlog::memory_buf_t &dest) = 0;
        [[nodiscard]] virtual std::unique_ptr<spdlog::custom_flag_formatter> clone() const = 0;
    };

}
