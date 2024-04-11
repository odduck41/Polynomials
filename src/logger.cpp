#include "../include/logger.h"
#include <chrono>
#include <ctime>
#include <cstring>

//#define PRINT_ERROR

std::ofstream Logger::os;

Logger::Logger(const char* filename_): filename(filename_) {
    os.open(filename_, std::ios::app);
}

Logger::~Logger() {
    os.flush();
    os.close();
}

void Logger::close() const {
    os.flush();
    os.close();
    Logger::os.open(filename, std::ios::app);
    os << "Program finished!\n\n";
    os.flush();
    os.close();
}

Logger operator<<(Logger& logger, const std::string& s) {
    Logger::os.flush();
    Logger::os.close();
    Logger::os.open(logger.filename, std::ios::app);
    auto seconds = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto time = ctime(&seconds);
    time[strlen(time) - 1] = '\0';
    Logger::os << time << ": " << s << "\n";
    Logger::os.flush();
#ifdef PRINT_ERROR
    std::cerr << time << ": " << s << "\n";
#endif
    return logger;
}
