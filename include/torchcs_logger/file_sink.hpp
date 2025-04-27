#pragma once

#include <spdlog/details/file_helper.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <ctime>
#include <fmt/format.h>

namespace torchcs
{
    class FileSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        explicit FileSink(std::string filename, size_t max_size);

    protected:
        void sink_it_(const spdlog::details::log_msg &msg) override;
        void flush_() override;

    private:
        void check_and_rotate_file();
        void rotate_daily_file();
        void update_filename();
        std::string generate_filename() const;

        std::string filename_;
        size_t max_size_;
        spdlog::details::file_helper file_helper_;
        std::string current_date_;
        std::string current_hour_;
    };
}
