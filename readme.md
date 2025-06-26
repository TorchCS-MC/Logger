## Description

TorchCS Logger is an extension of spdlog. It is generally used for console applications, such as bots or server software

## Required Tools

- **CMake 3.20+** (recommended)
- **A C++20 compiler:**
  - **Windows:** MSVC (Visual Studio 2022) or MinGW
  - **Linux:** GCC 11+ or Clang 14+

## CMake

```cmake
include(FetchContent)

FetchContent_Declare(
    torchcs_logger
    GIT_REPOSITORY https://github.com/TorchCS-MC/Logger.git
    GIT_TAG [release_version]
)

FetchContent_MakeAvailable(torchcs_logger)

target_link_libraries(your_project PRIVATE torchcs::logger)
```

## Example Code

```code
#include <torchcs/spdlog/spdlog_provider.hpp>
#include <torchcs/spdlog/sinks/console_sink.hpp>
#include <torchcs/spdlog/log_level.hpp>
#include <torchcs/spdlog/sinks/file_sink.hpp>

#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

int main() {
    auto my_console_sink = std::make_shared<torchcs::logger::sinks::ConsoleSink>();
    auto file_sink = std::make_shared<torchcs::logger::sinks::FileSink>("logs/cool", 1024 * 1024 * 5);

    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks = {my_console_sink, file_sink};
    auto console_logger = std::make_shared<spdlog::logger>("TorchCS", sinks.begin(), sinks.end());

    console_logger->set_level(spdlog::level::trace);

    torchcs::logger::SpdLogProvider provider(console_logger);

    provider.setLevel(torchcs::logger::level::Type::Trace);

    provider.log(torchcs::logger::level::Type::Info, torchcs::logger::color::Type::PINK + "Hello World");
    provider.log(torchcs::logger::level::Type::Info, "§aHello World");
    provider.log(torchcs::logger::level::Type::Debug, "Hello World");
    provider.log(torchcs::logger::level::Type::Warn, "Hello World");
    provider.log(torchcs::logger::level::Type::Error, "Hello World");

    return 0;
}
```

## License

This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for more details.
