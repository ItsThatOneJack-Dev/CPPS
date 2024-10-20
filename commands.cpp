#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

std::string joinvectorintostring(const std::vector<std::string>& elements, const std::string& delimiter) {
    std::ostringstream result;
    for (size_t i = 0; i < elements.size(); ++i) {
        result << elements[i];
        if (i < elements.size() - 1) {
            result << delimiter;  // Add delimiter between elements, but not after the last element
        }
    }
    return result.str();
}










void echo(const std::vector<std::string>& Arguments) {
    std::cout << joinvectorintostring(Arguments, " ") << std::endl;
}

void time(const std::vector<std::string>& Arguments) {
    std::cout << "It is: " << TimeUtils::todayDate("D/M/Y") << " at " << TimeUtils::secondAccuracy() << std::endl;
    std::cout << "Using date format: DD/MM/YYYY." << std::endl;
}

std::map<std::string,std::function<void(const std::vector<std::string>&)>> AllCommands = {
    {"echo", std::function<void(const std::vector<std::string>&)>(echo)},
    {"time", std::function<void(const std::vector<std::string>&)>(static_cast<void(*)(const std::vector<std::string>&)>(time))},
    {"date", std::function<void(const std::vector<std::string>&)>(static_cast<void(*)(const std::vector<std::string>&)>(time))}
};