#include "logger.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

// Constructor
Logger::Logger(const std::string& logFilePath) : logFilePath_(logFilePath) {
    // Open the log file
    logFile_.open(logFilePath_, std::ios::app);
    if (!logFile_.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath_ << std::endl;
    }
}

// Destructor
Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

// Get current time as string
std::string Logger::currentTime() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Log a message with INFO severity
void Logger::logInfo(const std::string& message) {
    if (logFile_.is_open()) {
        logFile_ << "[" << currentTime() << "] [INFO] " << message << std::endl;
    }
}

// Log a message with WARNING severity
void Logger::logWarning(const std::string& message) {
    if (logFile_.is_open()) {
        logFile_ << "[" << currentTime() << "] [WARNING] " << message << std::endl;
    }
}

// Log a message with ERROR severity
void Logger::logError(const std::string& message) {
    if (logFile_.is_open()) {
        logFile_ << "[" << currentTime() << "] [ERROR] " << message << std::endl;
    }
}
