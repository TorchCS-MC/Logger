#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class LoggerOptions {
private:
    fs::path log_path;
    std::string default_log_color;

public:
    void setLogPath(fs::path path);

    fs::path getLogPath() const;
};
