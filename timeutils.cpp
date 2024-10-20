#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

class TimeUtils {
public:
    // Get the current time with second accuracy (HH:MM:SS)
    static std::string secondAccuracy() {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        const std::tm* now_tm = std::localtime(&now_time_t);

        // Format the time to a string (HH:MM:SS)
        std::ostringstream oss;
        oss << std::put_time(now_tm, "%H:%M:%S"); // Only HH:MM:SS
        return oss.str();
    }

    // Get the current time with millisecond accuracy (HH:MM:SS.mmm)
    static std::string millisecondAccuracy() {
        const auto now = std::chrono::system_clock::now();
        const auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        const auto epoch = now_ms.time_since_epoch();
        const auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        // Calculate seconds and milliseconds
        const long seconds = value / 1000;
        const long milliseconds = value % 1000;

        // Convert to time_t and then to local time
        const std::time_t now_time_t = seconds;
        const std::tm* now_tm = std::localtime(&now_time_t);

        // Format the time to a string (HH:MM:SS.mmm)
        std::ostringstream oss;
        oss << std::put_time(now_tm, "%H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds; // Only HH:MM:SS.mmm
        return oss.str();
    }

    // Get today's date with custom format
    static std::string todayDate(const std::string& format) {
        const auto now = std::chrono::system_clock::now();
        const auto now_time_t = std::chrono::system_clock::to_time_t(now);
        const std::tm* now_tm = std::localtime(&now_time_t);

        std::ostringstream oss;

        for (const char c : format) {
            if (c == 'Y') {
                oss << std::setfill('0') << std::setw(4) << (now_tm->tm_year + 1900); // Full year
            } else if (c == 'y') {
                oss << std::setfill('0') << std::setw(2) << ((now_tm->tm_year + 1900) % 100); // 2-digit year
            } else if (c == 'M') {
                oss << std::setfill('0') << std::setw(2) << (now_tm->tm_mon + 1); // Month (01-12)
            } else if (c == 'D') {
                oss << std::setfill('0') << std::setw(2) << now_tm->tm_mday; // Day of the month (01-31)
            } else {
                oss << c; // Include the delimiter or other characters
            }
        }

        return oss.str();
    }
};
