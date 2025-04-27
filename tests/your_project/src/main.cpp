#include <torchcs_logger/spdlog_provider.hpp>
#include <torchcs_logger/console_sink.hpp>
#include <torchcs_logger/enums/log_level.hpp>
#include <torchcs_logger/file_sink.hpp>

#include <memory>

int main() {
    auto my_console_sink = std::make_shared<torchcs::ConsoleSink>();

    auto file_sink = std::make_shared<torchcs::FileSink>("logs.txt", 1024 * 1024 * 5);

    auto console_logger = std::make_shared<spdlog::logger>("TorchCS", file_sink);

    torchcs::SpdLogProvider provider(console_logger);
    provider.setLevel(torchcs::LogLevel::Trace);

    provider.log(torchcs::LogLevel::Error, "Hello World from TorchCS Logger!");

    provider.log(torchcs::LogLevel::Critical, "Hello World from TorchCS Logger!");

    provider.log(torchcs::LogLevel::Trace, "§aHello World from TorchCS Logger!");
    provider.log(torchcs::LogLevel::Warn, "Hello World from TorchCS Logger!");
    provider.log(torchcs::LogLevel::Debug, "Hello World from TorchCS Logger!");

    return 0;
}
