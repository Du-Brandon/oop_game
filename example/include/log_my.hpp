// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Logger {
    enum class Level {
        INFO,
        WARNING,
        ERROR
    };

    inline std::ofstream logFile;
    inline std::mutex logMutex;

    inline void init(const std::string& filename = "log.txt") {
        std::lock_guard<std::mutex> lock(logMutex);
        logFile.open(filename, std::ios::app);
        if (!logFile) {
            throw std::runtime_error("無法打開 log 檔案");
        }
    }

    inline std::string levelToString(Level level) {
        switch (level) {
            case Level::INFO: return "INFO";
            case Level::WARNING: return "WARNING";
            case Level::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

    inline void log(Level level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);

        if (!logFile.is_open()) {
            // optional: 自動初始化
            init(); 
        }

        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);

        logFile << "[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << "] "
                << "[" << levelToString(level) << "] "
                << message << std::endl;
    }

    // 快速介面
    inline void info(const std::string& msg)   { log(Level::INFO, msg); }
    inline void warn(const std::string& msg)   { log(Level::WARNING, msg); }
    inline void error(const std::string& msg)  { log(Level::ERROR, msg); }

    inline void shutdown() {
        std::lock_guard<std::mutex> lock(logMutex);
        if (logFile.is_open()) {
            logFile.close();
        }
    }
}

#endif
