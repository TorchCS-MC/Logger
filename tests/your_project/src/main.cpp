#include <torchcs_logger/custom_formatter.hpp>
#include <torchcs_logger/logger_manager.hpp>
#include <torchcs_logger/logger_options.hpp>

int main() {

    LoggerOptions options;

    options.setLogPath("logs");
    
    LoggerManager logger("Server");
    logger.file_logging(true);

    logger.load_options(options);

    logger.info("Hello World");
    logger.warn("Hello World");
    logger.error("Hello World");

    std::string name = "CheerfulVoice27";

    logger.info("Player name: {}", name);

    return 0;
}