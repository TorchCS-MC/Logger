#include <torchcs_logger/spdlog_provider.hpp>

namespace torchcs
{
    SpdLogProvider::SpdLogProvider(std::shared_ptr<spdlog::logger> logger) : logger_(std::move(logger)) {}

    std::string_view SpdLogProvider::getName() const
    {
        return logger_->name();
    }

    void SpdLogProvider::log(torchcs::LogLevel level, std::string_view message) const
    {
        if (!logger_) {
            return;
        }
        logger_->log(static_cast<spdlog::level::level_enum>(level), "{}", message);
    }


    void SpdLogProvider::setLevel(LogLevel level)
    {
        if (!logger_)
            return;

        logger_->set_level(static_cast<spdlog::level::level_enum>(level));
    }
}