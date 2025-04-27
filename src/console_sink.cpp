#include <torchcs_logger/console_sink.hpp>
#include <spdlog/sinks/stdout_color_sinks.h> 
#include <spdlog/sinks/base_sink-inl.h>

#include <torchcs_logger/level_formatter.hpp> 
#include <torchcs_logger/color_code_formatter.hpp>
#include <spdlog/details/fmt_helper.h> 
#include <cstdio>

#include <iostream>

namespace torchcs
{

    ConsoleSink::ConsoleSink(spdlog::color_mode mode)
    {
        setColorMode(mode);
        internal_sink_ = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(mode);

        level_colors_[spdlog::level::trace] = LogColor::LogColorToAnsi(LogColor::DARK_BLUE);
        level_colors_[spdlog::level::debug] = LogColor::LogColorToAnsi(LogColor::BLUE);
        level_colors_[spdlog::level::info] = LogColor::LogColorToAnsi(LogColor::RESET);
        level_colors_[spdlog::level::warn] = LogColor::LogColorToAnsi(LogColor::ORANGE);
        level_colors_[spdlog::level::err] = LogColor::LogColorToAnsi(LogColor::RED);
        level_colors_[spdlog::level::critical] = LogColor::LogColorToAnsi(LogColor::DARK_RED);
        level_colors_[spdlog::level::off] = LogColor::LogColorToAnsi(LogColor::WHITE);

        auto formatter = std::make_unique<spdlog::pattern_formatter>();

        formatter->add_flag<torchcs::LevelFormatter>('L');
        formatter->add_flag<torchcs::ColorCodeFormatter>('C');

        formatter->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%L] [%n] %v%$");

        formatter_ = std::move(formatter);
    }

    void ConsoleSink::setColorMode(spdlog::color_mode mode)
    {
        internal_sink_ = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(mode);
    }

    void ConsoleSink::sink_it_(const spdlog::details::log_msg& msg)
    {
        spdlog::memory_buf_t formatted;
        formatter_->format(msg, formatted);

        const std::string& color_code = level_colors_[msg.level];
        constexpr const char* reset_color = "\033[0m";

        fwrite(color_code.data(), sizeof(char), color_code.size(), stdout);
        fwrite(formatted.data(), sizeof(char), formatted.size(), stdout);
        fwrite(reset_color, sizeof(char), std::strlen(reset_color), stdout);
        fflush(stdout);
    }

    void ConsoleSink::flush_()
    {
        fflush(stdout);
    }

}
