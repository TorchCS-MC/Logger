#include <torchcs/spdlog/sinks/console_sink.hpp>
#include "formatter/level_formatter.hpp"
#include "formatter/color_code_formatter.hpp"

#include <spdlog/sinks/stdout_color_sinks.h> 
#include <spdlog/sinks/base_sink-inl.h>
#include <spdlog/details/fmt_helper.h> 

#include <cstdio>
#include <iostream>

namespace torchcs::logger::sinks
{

    ConsoleSink::ConsoleSink(spdlog::color_mode mode)
    {
        setColorMode(mode);
        internal_sink_ = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(mode);

        level_colors_[spdlog::level::trace] = color::Type::LogColorToAnsi(color::Type::DARK_BLUE);
        level_colors_[spdlog::level::debug] = color::Type::LogColorToAnsi(color::Type::BLUE);
        level_colors_[spdlog::level::info] = color::Type::LogColorToAnsi(color::Type::WHITE);
        level_colors_[spdlog::level::warn] = color::Type::LogColorToAnsi(color::Type::ORANGE);
        level_colors_[spdlog::level::err] = color::Type::LogColorToAnsi(color::Type::RED);
        level_colors_[spdlog::level::critical] = color::Type::LogColorToAnsi(color::Type::DARK_RED);
        level_colors_[spdlog::level::off] = color::Type::LogColorToAnsi(color::Type::WHITE);

        auto formatter = std::make_unique<spdlog::pattern_formatter>();

        formatter->add_flag<torchcs::logger::formatter::LevelFormatter>('L');
        formatter->add_flag<torchcs::logger::formatter::ColorCodeFormatter>('C');

        formatter->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%L] [%n] %C");

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
    
        std::string formatted_str = fmt::to_string(formatted);
        std::string ansi_text = color::Type::ColorCodeToFormattedText(formatted_str);
    
        fwrite(color_code.data(), sizeof(char), color_code.size(), stdout);
        fwrite(ansi_text.data(), sizeof(char), ansi_text.size(), stdout);
        fwrite(reset_color, sizeof(char), std::strlen(reset_color), stdout);
        fflush(stdout);
    }
    

    void ConsoleSink::flush_()
    {
        fflush(stdout);
    }

}
