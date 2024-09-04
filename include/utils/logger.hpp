#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

class Logger {
public:
    // Enum for log levels
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    // Constructor
    Logger(const std::string& log_file);

    // Destructor
    ~Logger();

    // Log a message with a specific log level
    void log(LogLevel level, const std::string& message);

private:
    // Convert LogLevel enum to string
    std::string logLevelToString(LogLevel level) const;

    // Log file stream
    std::ofstream log_file_stream_;

    // Mutex for thread safety
    std::mutex log_mutex_;
};

#endif // LOGGER_HPP
