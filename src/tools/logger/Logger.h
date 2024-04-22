#pragma once

#include <string>
#include <vector>

enum LogType {
    INFO,
    WARN,
    ERROR
};

struct LogEntry {
    LogType type;
    std::string message;
};

class Logger {
public:
    static std::vector<LogEntry> logs;

    /**
     * @brief Log a info message to the console in the color GREEN
     * @param message Message to log
    */
    static void Info(std::string message);
    
    /**
     * @brief Log a warning message to the console in the color YELLOW
     * @param message Message to log
    */
    static void Warn(std::string message);

    /**
     * @brief Log a error message to the console in the color RED
     * @param message Message to log
    */
    static void Error(std::string message);
};