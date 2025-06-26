#include "torchcs/spdlog/spdlog_provider.hpp"

namespace torchcs::logger
{
    SpdLogProvider::SpdLogProvider(std::shared_ptr<spdlog::logger> logger) : logger_(std::move(logger)) {}

    std::string_view SpdLogProvider::getName() const
    {
        return logger_->name();
    }

    void SpdLogProvider::log(torchcs::logger::level::Type level, std::string_view message) const
    {
        if (!logger_) {
            return;
        }
        logger_->log(static_cast<spdlog::level::level_enum>(level), "{}", message);
    }


    void SpdLogProvider::setLevel(torchcs::logger::level::Type level)
    {
        if (!logger_)
            return;

        logger_->set_level(static_cast<spdlog::level::level_enum>(level));
    }
}