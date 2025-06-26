#include <torchcs/spdlog/sinks/file_sink.hpp>
#include "formatter/level_formatter.hpp"
#include "formatter/anti_color_code_formatter.hpp"

#include <spdlog/pattern_formatter.h>
#include <spdlog/details/file_helper.h>
#include <fmt/format.h>

#include <ctime>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using spdlog::details::os::path_exists;


namespace torchcs::logger::sinks
{

    FileSink::FileSink(spdlog::filename_t base_filename, size_t max_size) : max_size_(max_size)
    {
        filename_ = generate_filename(base_filename);

        auto parent_path = fs::path(filename_).parent_path();
        
        if (!parent_path.empty() && !fs::exists(parent_path))
        {
            fs::create_directories(parent_path);
        }

        try
        {
            file_helper_.open(filename_);
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cerr << "Logger file open error: " << ex.what() << std::endl;
            throw;
        }

        auto formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->add_flag<torchcs::logger::formatter::LevelFormatter>('L');
        formatter->add_flag<torchcs::logger::formatter::AntiColorCodeFormatter>('C');
        formatter->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%L] [%n] %C");

        this->set_formatter(std::move(formatter));
    }

    std::string FileSink::generate_filename(const std::string &base) const
    {
        std::time_t t = std::time(nullptr);
        std::tm tm;

#ifdef WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif

        return fmt::format("{}_{:02d}.{:02d}.{:04d}_{:02d}.txt", base, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour);
    }

    void FileSink::sink_it_(const spdlog::details::log_msg &msg)
    {
        spdlog::memory_buf_t formatted;
        this->formatter_->format(msg, formatted);

        check_and_rotate_file();
        file_helper_.write(formatted);
    }

    void FileSink::flush_()
    {
        file_helper_.flush();
    }

    void FileSink::check_and_rotate_file()
    {
        std::fstream file(filename_, std::ios::in | std::ios::binary);
        file.seekg(0, std::ios::end);
        size_t current_size = static_cast<size_t>(file.tellg());

        if (current_size > max_size_)
        {
            file_helper_.close();

            std::stringstream archive_filename;
            archive_filename << filename_ << "." << std::time(nullptr);
            std::rename(filename_.c_str(), archive_filename.str().c_str());

            file_helper_.open(filename_);
        }

        rotate_daily_file();
    }

    void FileSink::rotate_daily_file()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm;

#ifdef WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif

        std::string new_date = fmt::format("{:04d}.{:02d}.{:02d}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        std::string new_hour = fmt::format("{:02d}", tm.tm_hour);

        if (new_date != current_date_ || new_hour != current_hour_)
        {
            file_helper_.close();

            std::stringstream archive_filename;
            archive_filename << filename_ << "." << new_date << "-" << new_hour;
            std::rename(filename_.c_str(), archive_filename.str().c_str());

            file_helper_.open(filename_);
            current_date_ = new_date;
            current_hour_ = new_hour;
        }
    }

    void FileSink::update_filename()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm;

#ifdef WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif

        current_date_ = fmt::format("{:04d}.{:02d}.{:02d}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        current_hour_ = fmt::format("{:02d}", tm.tm_hour);

        file_helper_.close();

        std::stringstream archive_filename;
        archive_filename << filename_ << "." << current_date_ << "-" << current_hour_;
        std::rename(filename_.c_str(), archive_filename.str().c_str());

        file_helper_.open(filename_);
    }
}
