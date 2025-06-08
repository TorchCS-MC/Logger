#pragma once

#include <string>

struct LogColor {
    static const std::string BLACK;
    static const std::string DARK_BLUE;
    static const std::string DARK_GREEN;
    static const std::string DARK_AQUA;
    static const std::string DARK_RED;
    static const std::string DARK_PURPLE;
    static const std::string ORANGE;
    static const std::string GRAY;
    static const std::string DARK_GRAY;
    static const std::string BLUE;
    static const std::string GREEN;
    static const std::string AQUA;
    static const std::string RED;
    static const std::string PINK;
    static const std::string YELLOW;
    static const std::string WHITE;
    static const std::string BOLD;
    static const std::string RESET;

    static std::string LogColorToAnsi(const std::string &colorCode);
    static std::string ColorCodeToFormattedText(const std::string &text);
    static std::string RemoveAllColorCodeFromText(const std::string &text);
};
