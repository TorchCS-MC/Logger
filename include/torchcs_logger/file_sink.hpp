#pragma once

#include <spdlog/details/file_helper.h>
#include <spdlog/details/os.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>

namespace torchcs
{

    class FileSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        explicit FileSink(spdlog::filename_t filename, size_t max_size = 10 * 1024 * 1024);
        void set_max_size(size_t max_size);

    protected:
        void sink_it_(const spdlog::details::log_msg &msg) override;
        void flush_() override;

    private:
        std::ofstream log_file_;
        std::string filename_;
        size_t max_size_;
        void check_and_rotate_file();
    };

}
