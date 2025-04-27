#pragma once

#include "interfaces/IProvider.hpp"
#include <spdlog/logger.h>

namespace torchcs
{

    class SpdLogProvider : public IProvider
    {
    private:
        std::shared_ptr<spdlog::logger> logger_;

    public:
        explicit SpdLogProvider(std::shared_ptr<spdlog::logger> logger);

        [[nodiscard]] std::string_view getName() const override;

        void log(LogLevel level, std::string_view message) const override;

        void setLevel(LogLevel level) override;

    };

}
