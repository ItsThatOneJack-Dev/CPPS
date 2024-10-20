#include <string>

std::string ANSI_CSI = "\033[";

std::string ANSI_RESET = "\033[0m";
std::string ANSI_BRIGHT = "\033[1m";
std::string ANSI_FAINT = "\033[2m";
std::string ANSI_ITALIC = "\033[3m";
std::string ANSI_UNDERLINE = "\033[4m";
std::string ANSI_SLOWBLINK = "\033[5m";
std::string ANSI_RAPIDBLINK = "\033[6m";
std::string ANSI_INVERT = "\033[7m";
std::string ANSI_HIDE = "\033[8m";
std::string ANSI_STRIKETHROUGH = "\033[9m";
std::string ANSI_DEFAULT_FONT = "\033[10m";
std::string ANSI_ALTERNATIVE_FONT_1 = "\033[11m";
std::string ANSI_ALTERNATIVE_FONT_2 = "\033[12m";
std::string ANSI_ALTERNATIVE_FONT_3 = "\033[13m";
std::string ANSI_ALTERNATIVE_FONT_4 = "\033[14m";
std::string ANSI_ALTERNATIVE_FONT_5 = "\033[15m";
std::string ANSI_ALTERNATIVE_FONT_6 = "\033[16m";
std::string ANSI_ALTERNATIVE_FONT_7 = "\033[17m";
std::string ANSI_ALTERNATIVE_FONT_8 = "\033[18m";
std::string ANSI_ALTERNATIVE_FONT_9 = "\033[19m";
std::string ANSI_GOTHIC_FONT = "\033[20m";
std::string ANSI_DOUBLE_UNDERLINE = "\033[21m";
std::string ANSI_NORMAL_BRIGHTNESS = "\033[22m";
std::string ANSI_NEITHER_ITALIC_NOR_BLACKLETTER = "\033[23m";
std::string ANSI_NOT_UNDERLINED = "\033[24m";
std::string ANSI_NOT_BLINKING = "\033[25m";
std::string ANSI_PROPORTIONAL_SPACING = "\033[26m";
std::string ANSI_NOT_REVERSED = "\033[27m";
std::string ANSI_SHOW_UNDERLINE = "\033[30m";
std::string ANSI_NOT_STRIKETHROUGH = "\033[31m";
std::string ANSI_GENERATE_8BIT_FOREGROUND(const int& ColourID) {
    return "\033[38;5;" + std::to_string(ColourID) + "m";
}
std::string ANSI_GENERATE_RGB_FOREGROUND(const int& Red, const int& Green, const int& Blue) {
    return "\033[38;2;" + std::to_string(Red) + ";" + std::to_string(Green) + ";" + std::to_string(Blue) + "m";
}
std::string ANSI_DEFAULT_FOREGROUND = "\033[39m";
std::string ANSI_GENERATE_8BIT_BACKGROUND(const int& ColourID) {
    return "\033[48;5;" + std::to_string(ColourID) + "m";
}
std::string ANSI_GENERATE_RGB_BACKGROUND(const int& Red, const int& Green, const int& Blue) {
    return "\033[48;2;" + std::to_string(Red) + ";" + std::to_string(Green) + ";" + std::to_string(Blue) + "m";
}
std::string ANSI_DEFAULT_BACKGROUND = "\033[49m";
std::string ANSI_NOT_PROPORTIONALLY_SPACED = "\033[50m";
std::string ANSI_FRAMED = "\033[51m";
std::string ANSI_ENCIRCLED = "\033[52m";
std::string ANSI_OVERLINED = "\033[53m";
std::string ANSI_NEITHER_FRAMED_NOR_ENCIRCLED = "\033[54m";
std::string ANSI_NOT_OVERLINED = "\033[55m";
std::string ANSI_GENERATE_8BIT_UNDERLINE(const int& ColourID) {
    return "\033[58;5;" + std::to_string(ColourID) + "m";
}
std::string ANSI_GENERATE_RGB_UNDERLINE(const int& Red, const int& Green, const int& Blue) {
    return "\033[58;2;" + std::to_string(Red) + ";" + std::to_string(Green) + ";" + std::to_string(Blue) + "m";
}
std::string ANSI_DEFAULT_UNDERLINE = "\033[59m";
std::string ANSI_IDEOGRAM_UNDERLINE = "\033[60m";
std::string ANSI_IDEOGRAM_DOUBLE_UNDERLINE = "\033[61m";
std::string ANSI_IDEOGRAM_OVERLINE = "\033[62m";
std::string ANSI_IDEOGRAM_DOUBLE_OVERLINE = "\033[63m";
std::string ANSI_IDEOGRAM_STRESS = "\033[64m";
std::string ANSI_IDEOGRAM_RESET = "\033[65m";
std::string ANSI_SUPERSCRIPT = "\033[73m";
std::string ANSI_SUBSCRIPT = "\033[74m";
std::string ANSI_NEITHER_SUPERSCRIPT_NOR_SUBSCRIPT = "\033[75m";
std::string ANSI_GENERATE_MASKED_LINK(const std::string& Link, const std::string& Text) {
    return "\x1b]8;;"+Link+"\x07"+Text+"\x1b]8;;\x07";
}