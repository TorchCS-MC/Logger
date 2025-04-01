#ifndef TORCHCS_LOGGER_LOGLEVEL_HPP
#define TORCHCS_LOGGER_LOGLEVEL_HPP

#include <string>
#include <spdlog/spdlog.h>

enum LogLevel : unsigned int {
    Debug,
    Verbose,
    Info,
    Warn,
    Error,
    Critical
};


#endif
