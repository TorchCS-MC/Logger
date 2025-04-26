#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/formatter.h>
#include <memory>

class CustomFileFormatter : public spdlog::formatter {
public:
    CustomFileFormatter() = default;
    ~CustomFileFormatter() override = default;

    void format(const spdlog::details::log_msg& msg, spdlog::memory_buf_t& dest) override;
    std::unique_ptr<spdlog::formatter> clone() const override;
};
