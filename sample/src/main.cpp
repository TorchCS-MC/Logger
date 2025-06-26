#include <torchcs/spdlog/spdlog_provider.hpp>
#include <torchcs/spdlog/sinks/console_sink.hpp>
#include <torchcs/spdlog/log_level.hpp>
#include <torchcs/spdlog/sinks/file_sink.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

int main() {
    auto my_console_sink = std::make_shared<torchcs::logger::sinks::ConsoleSink>();
    auto file_sink = std::make_shared<torchcs::logger::sinks::FileSink>("logs/cool", 1024 * 1024 * 5);

    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks = {my_console_sink, file_sink};
    auto console_logger = std::make_shared<spdlog::logger>("TorchCS", sinks.begin(), sinks.end());

    console_logger->set_level(spdlog::level::trace);

    torchcs::logger::SpdLogProvider provider(console_logger);

    provider.setLevel(torchcs::logger::level::Type::Trace);

    provider.log(torchcs::logger::level::Type::Info, torchcs::logger::color::Type::PINK + "Hello World");
    provider.log(torchcs::logger::level::Type::Info, "§aHello World");
    provider.log(torchcs::logger::level::Type::Info, "§aHello World");
    provider.log(torchcs::logger::level::Type::Info, "§aHello World");
    provider.log(torchcs::logger::level::Type::Info, "Hello World");
    provider.log(torchcs::logger::level::Type::Debug, "Hello World");
    provider.log(torchcs::logger::level::Type::Warn, "Hello World");
    provider.log(torchcs::logger::level::Type::Error, "Hello World");

    return 0;
}
