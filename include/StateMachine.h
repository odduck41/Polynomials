#pragma once

#include <string>

class Devil : public std::exception {
  public:
    explicit Devil(std::string msg): errorMessage(std::move(msg)) {};

    [[nodiscard]] const char *what() const noexcept override {
        return errorMessage.c_str();
    }

  private:
    std::string errorMessage;
};

class string_error : public std::exception {
  public:
    explicit string_error(std::string msg): errorMessage(std::move(msg)) {};

    [[nodiscard]] const char *what() const noexcept override {
        return errorMessage.c_str();
    }

  private:
    std::string errorMessage;
};

bool stateMachine(const std::string&, size_t = 0, int = -1);
