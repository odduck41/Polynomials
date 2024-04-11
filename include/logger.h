#include <iostream>
#include <fstream>

struct Logger {
    explicit Logger(const char * = "../.log");
    void close() const;
    ~Logger();
    static std::ofstream os;
    const char* filename;
};

Logger operator<<(Logger&, const std::string&);
