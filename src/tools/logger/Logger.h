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
    static void Info(std::string message);
    static void Warn(std::string message);
    static void Error(std::string message);
};