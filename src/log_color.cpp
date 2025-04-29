#include <torchcs_logger/log_color.hpp>
#include <unordered_map>

const std::string LogColor::BLACK = "§0";
const std::string LogColor::DARK_BLUE = "§1";
const std::string LogColor::DARK_GREEN = "§2";
const std::string LogColor::DARK_AQUA = "§3";
const std::string LogColor::DARK_RED = "§4";
const std::string LogColor::DARK_PURPLE = "§5";
const std::string LogColor::ORANGE = "§6";
const std::string LogColor::GRAY = "§7";
const std::string LogColor::DARK_GRAY = "§8";
const std::string LogColor::BLUE = "§9";
const std::string LogColor::GREEN = "§a";
const std::string LogColor::AQUA = "§b";
const std::string LogColor::RED = "§c";
const std::string LogColor::PINK = "§d";
const std::string LogColor::YELLOW = "§e";
const std::string LogColor::WHITE = "§f";
const std::string LogColor::BOLD = "§l";
const std::string LogColor::RESET = "§r";

std::string LogColor::LogColorToAnsi(const std::string &colorCode)
{
    static const std::unordered_map<std::string, std::string> colorMap = {
        {BLACK, "\033[30m"}, {DARK_BLUE, "\033[34m"}, {DARK_GREEN, "\033[32m"}, {DARK_AQUA, "\033[36m"}, {DARK_RED, "\033[31m"}, {DARK_PURPLE, "\033[35m"}, {ORANGE, "\033[38;2;255;140;0m"}, {GRAY, "\033[37m"}, {DARK_GRAY, "\033[90m"}, {BLUE, "\033[94m"}, {GREEN, "\033[92m"}, {AQUA, "\033[96m"}, {RED, "\033[91m"}, {PINK, "\033[95m"}, {YELLOW, "\033[93m"}, {WHITE, "\033[97m"}, {BOLD, "\033[1m"}, {RESET, "\033[0m"}};

    auto it = colorMap.find(colorCode);
    return (it != colorMap.end()) ? it->second : "\033[0m";
}

std::string LogColor::ColorCodeToFormattedText(const std::string &text)
{
    std::string result;
    size_t len = text.length();

    for (size_t i = 0; i < len; ++i)
    {
        if (text[i] == '\xA7' && i + 1 < len)
        {
            char code = text[i + 1];
            std::string mc_code = std::string("§") + code;
            result += LogColorToAnsi(mc_code);
            i += 1;
        }
        else if ((unsigned char)text[i] == 0xC2 && i + 2 < len && (unsigned char)text[i + 1] == 0xA7)
        {
            char code = text[i + 2];
            std::string mc_code = std::string("§") + code;
            result += LogColorToAnsi(mc_code);
            i += 2;
        }
        else
        {
            result += text[i];
        }
    }

    result += LogColorToAnsi(RESET);
    return result;
}

std::string LogColor::RemoveAllColorCodeFromText(const std::string &text)
{
    std::string result;
    size_t len = text.length();

    for (size_t i = 0; i < len; ++i)
    {
        if (text[i] == '\xA7' && i + 1 < len)
        {
            i += 1;
        }
        else if ((unsigned char)text[i] == 0xC2 && i + 2 < len && (unsigned char)text[i + 1] == 0xA7)
        {
            i += 2;
        }
        else
        {
            result += text[i];
        }
    }

    return result;
}
