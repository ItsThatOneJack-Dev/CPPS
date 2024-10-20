#include "modulesource.cpp"
#include <iostream>
#include <string>

void positiveOutput(const std::string Text) {
  std::cout << ANSI_GENERATE_RGB_FOREGROUND(0,255,0) << ANSI_BRIGHT << "[+]" << ANSI_NORMAL_BRIGHTNESS << Text << ANSI_RESET << std::endl;
}
void negativeOutput(const std::string Text) {
  std::cout << ANSI_GENERATE_RGB_FOREGROUND(255,0,0) << ANSI_BRIGHT << "[-]" << ANSI_NORMAL_BRIGHTNESS << Text << ANSI_RESET << std::endl;
}