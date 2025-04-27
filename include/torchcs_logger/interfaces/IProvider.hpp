#pragma once

#include "../enums/log_level.hpp"
#include <fmt/format.h>
#include <string_view>

namespace torchcs {

    class IProvider {
    public:
        virtual ~IProvider() = default;

        [[nodiscard]] virtual std::string_view getName() const = 0;
        
        virtual void log(LogLevel level, std::string_view message) const = 0;
        virtual void setLevel(LogLevel level) = 0;

    };

}
