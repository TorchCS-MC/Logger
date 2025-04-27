#include <torchcs_logger/spdlog_provider.hpp>
#include <torchcs_logger/console_sink.hpp>
#include <torchcs_logger/enums/log_level.hpp>
#include <torchcs_logger/file_sink.hpp>
#include <spdlog/spdlog.h>
#include <memory>
#include <vector>

int main() {
    // Console Sink erstellen
    auto my_console_sink = std::make_shared<torchcs::ConsoleSink>();

    // File Sink erstellen
    auto file_sink = std::make_shared<torchcs::FileSink>("logs", 1024 * 1024 * 5);

    // Ein Vektor von Sinks erstellen
    //std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks = {my_console_sink, file_sink};

    // Logger erstellen und Sinks hinzufügen
    //auto console_logger = std::make_shared<spdlog::logger>("TorchCS", sinks.begin(), sinks.end());

    // Logger Level setzen
    //console_logger->set_level(spdlog::level::trace);



    return 0;
}
