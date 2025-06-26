#pragma once

#include <string_view>

namespace torchcs::logger::level
{
    enum class Type : unsigned int
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };
}
