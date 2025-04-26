#include <torchcs_logger/logger_manager.hpp>
#include <torchcs_logger/logger_options.hpp>

#include <thread> 
#include <chrono>

int main() {

    LoggerOptions options;
    options.setLogPath("logs");
    
    LoggerManager logger;

    logger.load_options(options);
    logger.set_flush_on_level(LogLevel::Value::Info);

    logger.log(LogLevel::Value::Info, "DATABASE", "COOOL");
    logger.log(LogLevel::Value::Info, "DATABASE", "COOOL");
    logger.log(LogLevel::Value::Info, "DATABASE", "COOOL");   

    return 0;
}