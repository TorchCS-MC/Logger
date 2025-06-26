#pragma once

#include "torchcs/spdlog/log_level.hpp"

#include <fmt/format.h>
#include <string_view>

namespace torchcs::logger::interfaces {

    class IProvider {
    public:
        virtual ~IProvider() = default;

        [[nodiscard]] virtual std::string_view getName() const = 0;
        
        virtual void log(logger::LogLevel level, std::string_view message) const = 0;
        virtual void setLevel(logger::LogLevel level) = 0;

    };

}
