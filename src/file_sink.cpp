#include <torchcs_logger/file_sink.hpp>
#include <spdlog/pattern_formatter.h>
#include <torchcs_logger/level_formatter.hpp>
#include <torchcs_logger/anti_color_code_formatter.hpp>
#include <spdlog/details/file_helper.h>
#include <ctime>
#include <fmt/format.h>

namespace torchcs
{

    FileSink::FileSink(std::string filename, size_t max_size)
        : filename_(std::move(filename)), max_size_(max_size)
    {

        update_filename();
        file_helper_.open(generate_filename());

        auto formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->add_flag<torchcs::LevelFormatter>('L');
        formatter->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%L] [%n] %v%$");

        this->set_formatter(std::move(formatter));
    }

    void FileSink::sink_it_(const spdlog::details::log_msg &msg)
    {
        spdlog::memory_buf_t formatted;
        this->formatter_->format(msg, formatted);
        check_and_rotate_file();
        file_helper_.write(static_cast<const spdlog::memory_buf_t &>(formatted));
    }

    void FileSink::flush_()
    {
        file_helper_.flush();
    }

    void FileSink::check_and_rotate_file()
    {
        std::fstream file(generate_filename(), std::ios::in | std::ios::binary);
        file.seekg(0, std::ios::end);
        size_t current_size = static_cast<size_t>(file.tellg());

        if (current_size > max_size_)
        {
            file_helper_.close();
            std::stringstream archive_filename;
            archive_filename << generate_filename() << "." << std::time(nullptr);
            std::rename(generate_filename().c_str(), archive_filename.str().c_str());

            file_helper_.open(generate_filename(), std::ios::app);
        }

        rotate_daily_file();
    }

    void FileSink::rotate_daily_file()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);

        std::string new_date = fmt::format("{:04d}_{:02d}_{:02d}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        std::string new_hour = fmt::format("{:02d}", tm.tm_hour);

        if (new_date != current_date_ || new_hour != current_hour_)
        {
            file_helper_.close();

            std::stringstream archive_filename;
            archive_filename << generate_filename() << "_" << new_date << "_" << new_hour;
            std::rename(generate_filename().c_str(), archive_filename.str().c_str());

            file_helper_.open(generate_filename(), std::ios::app);
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
        localtime_r(&tm, &t);
        #endif

        current_date_ = fmt::format("{:04d}_{:02d}_{:02d}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        current_hour_ = fmt::format("{:02d}", tm.tm_hour);
    }

    std::string FileSink::generate_filename() const
    {
        std::string filename = "logs/" + filename_ + "_" + current_date_ + "_" + current_hour_ + ".txt";
        return filename;
    }

}
