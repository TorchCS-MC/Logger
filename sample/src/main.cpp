#include <torchcs/spdlog/spdlog_provider.hpp>
#include <torchcs/spdlog/console_sink.hpp>
#include <torchcs/spdlog/log_level.hpp>
#include <torchcs/spdlog/file_sink.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

int main() {
    auto my_console_sink = std::make_shared<torchcs::ConsoleSink>();

    auto file_sink = std::make_shared<torchcs::FileSink>("logs/cool", 1024 * 1024 * 5);

    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks = {my_console_sink, file_sink};

    auto console_logger = std::make_shared<spdlog::logger>("TorchCS", sinks.begin(), sinks.end());
    console_logger->info("Normal: Hello World");
    console_logger->info("Normal: Hello World");
    console_logger->info("Normal: Hello World");
    console_logger->info("Normal: Hello World");
    console_logger->info("Hello World");

    console_logger->info("Hello World");

    console_logger->info("Hello World");

    console_logger->info("Hello World");


    console_logger->set_level(spdlog::level::trace);

    torchcs::SpdLogProvider provider(console_logger);

    provider.setLevel(torchcs::logger::LogLevel::Trace);

    provider.log(torchcs::logger::LogLevel::Info, LogColor::PINK + "Hello World");
    provider.log(torchcs::logger::LogLevel::Info, "§aHello World");
    provider.log(torchcs::logger::LogLevel::Info, "§aHello World");
    provider.log(torchcs::logger::LogLevel::Info, "§aHello World");
    provider.log(torchcs::logger::LogLevel::Info, "Hello World");
    provider.log(torchcs::logger::LogLevel::Debug, "Hello World");
    provider.log(torchcs::logger::LogLevel::Warn, "Hello World");
    provider.log(torchcs::logger::LogLevel::Error, "Hello World");

    return 0;
}
