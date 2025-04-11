#pragma once

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

