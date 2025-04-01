#ifndef TORCHCS_LOGGER_CUSTOMFORMATTER_H
#define TORCHCS_LOGGER_CUSTOMFORMATTER_H

#include <spdlog/spdlog.h>
#include <spdlog/formatter.h>
#include <fmt/format.h>
#include <ctime>
#include <memory>
#include <unordered_map>

class CustomFormatter : public spdlog::formatter {
private:
    std::string convert_minecraft_colors(const std::string& input);

public:
    void format(const spdlog::details::log_msg& msg, spdlog::memory_buf_t& dest) override;
    std::unique_ptr<spdlog::formatter> clone() const override;
};


#endif
