#pragma once

#include "../log_color.hpp"

#include <spdlog/details/console_globals.h>
#include <spdlog/details/os.h>
#include <spdlog/sinks/base_sink.h>

#include <memory>
#include <array>

namespace torchcs::logger::sinks
{
    class ConsoleSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        explicit ConsoleSink(spdlog::color_mode mode = spdlog::color_mode::automatic);
        void setColorMode(spdlog::color_mode mode);

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override;
        void flush_() override;

    private:
        color::Type color;
        std::shared_ptr<spdlog::sinks::sink> internal_sink_;
        std::array<std::string, spdlog::level::n_levels> level_colors_;

    };

}
