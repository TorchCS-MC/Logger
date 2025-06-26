#pragma once

#include "log_level.hpp"
#include <spdlog/logger.h>

namespace torchcs::logger
{
    class SpdLogProvider
    {
    private:
        std::shared_ptr<spdlog::logger> logger_;

    public:
        explicit SpdLogProvider(std::shared_ptr<spdlog::logger> logger);

        [[nodiscard]] std::string_view getName() const;

        void log(logger::level::Type level, std::string_view message) const;

        void setLevel(logger::level::Type level);

    };

}
