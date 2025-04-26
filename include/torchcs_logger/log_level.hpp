#pragma once

#include <string>

struct LogLevel {
    
    enum Value : unsigned int {
        Debug,
        Verbose,
        Info,
        Warn,
        Error,
        Critical
    };

    static inline std::string to_string(Value level) {
        switch (level) {
            case Debug: 
                return "DEBUG";
            case Verbose: 
                return "VERBOSE";
            case Info: 
                return "INFO";
            case Warn: 
                return "WARN";
            case Error: 
                return "ERROR";
            case Critical: 
                return "CRITICAL";
            default: 
                return "UNKNOWN";
        }
    }
};
