#include <torchcs_logger/file_sink.hpp>
#include <spdlog/pattern_formatter.h>
#include <torchcs_logger/level_formatter.hpp>
#include <torchcs_logger/anti_color_code_formatter.hpp>

namespace torchcs {

    FileSink::FileSink(spdlog::filename_t filename, size_t max_size)
        : filename_(std::move(filename)), max_size_(max_size) {

        log_file_.open(filename_, std::ios::app);
        if (!log_file_.is_open()) {
            throw std::runtime_error("Failed to open log file.");
        }

        auto formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->add_flag<torchcs::LevelFormatter>('L');
        formatter->add_flag<torchcs::AntiColorCodeFormatter>('C');
        formatter->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%L] [%n] %C");

        this->set_formatter(std::move(formatter));
    }

    void FileSink::sink_it_(const spdlog::details::log_msg &msg) {
        spdlog::memory_buf_t formatted;
        this->formatter_->format(msg, formatted);
        check_and_rotate_file();
        log_file_ << std::string_view(formatted.data(), formatted.size()) << std::endl;
    }

    void FileSink::flush_() {
        log_file_.flush();
    }

    void FileSink::check_and_rotate_file() {
        log_file_.seekp(0, std::ios::end);
        auto current_pos = log_file_.tellp();
        if (current_pos < 0) {
            throw std::runtime_error("Failed to determine the current file position.");
        }
        size_t current_size = static_cast<size_t>(current_pos);

        if (current_size > max_size_) {
            log_file_.close();

            std::stringstream archive_filename;
            archive_filename << filename_ << "." << std::time(nullptr); 
            std::rename(filename_.c_str(), archive_filename.str().c_str());

            log_file_.open(filename_, std::ios::app);
            if (!log_file_.is_open()) {
                throw std::runtime_error("Failed to reopen log file after rotation.");
            }
        }
    }

}
