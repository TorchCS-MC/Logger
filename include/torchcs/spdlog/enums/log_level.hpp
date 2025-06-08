#pragma once

#include <string_view>

namespace torchcs
{

    enum class LogLevel : unsigned int
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };

    constexpr std::string_view to_string(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Trace:
            return "TRACE";
        case LogLevel::Debug:
            return "DEBUG";
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Warn:
            return "WARN";
        case LogLevel::Error:
            return "ERROR";
        case LogLevel::Critical:
            return "CRITICAL";
        case LogLevel::Off:
            return "OFF";
        default:
            return "UNKNOWN";
        }
    }

}
