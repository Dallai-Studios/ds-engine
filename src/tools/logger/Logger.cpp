#include "Logger.h"
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET "\033[0m"

std::vector<LogEntry> Logger::logs;

std::string GetCurrentDateTimeAsString() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
    return output;
}

void CreateLogEntry(LogType type, std::string message) {
    LogEntry entry;
    entry.type = type;
    entry.message = message;
    Logger::logs.push_back(entry);
}

void Logger::Info(std::string message) {
    std::string currentDate = GetCurrentDateTimeAsString();
    std::string finalMessage = "[INFO] -- " + currentDate + " -- " + message;
    std::cout << GREEN << finalMessage << RESET << std::endl;
    CreateLogEntry(LogType::INFO, finalMessage);
}

void Logger::Warn(std::string message) {
    std::string currentDate = GetCurrentDateTimeAsString();
    std::string finalMessage = "[WARNING] -- " + currentDate + " -- " + message;
    std::cout << YELLOW << finalMessage << RESET << std::endl;
    CreateLogEntry(LogType::WARN, finalMessage);
}

void Logger::Error(std::string message) {
    std::string currentDate = GetCurrentDateTimeAsString();
    std::string finalMessage = "[ERROR] -- " + currentDate + " -- " + message;
    std::cout << RED << finalMessage << RESET << std::endl;
    CreateLogEntry(LogType::ERROR, finalMessage);
}