#pragma once

#include "log_level.hpp"
#include "interfaces/IProvider.hpp"
#include <spdlog/logger.h>

namespace torchcs::logger
{

    class SpdLogProvider : public logger::interfaces::IProvider
    {
    private:
        std::shared_ptr<spdlog::logger> logger_;

    public:
        explicit SpdLogProvider(std::shared_ptr<spdlog::logger> logger);

        [[nodiscard]] std::string_view getName() const override;

        void log(logger::LogLevel level, std::string_view message) const override;

        void setLevel(logger::LogLevel level) override;

    };

}
