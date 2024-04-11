#pragma once

#include "List.h"
#include <vector>
// Polynomial

class user_is_eight_years_old : public std::exception {
  public:
    explicit user_is_eight_years_old(std::string msg): errorMessage(std::move(msg)) {};

    [[nodiscard]] const char *what() const noexcept override {
        return errorMessage.c_str();
    }

  private:
    std::string errorMessage;
};


struct Monomial {
    Monomial() = default;

    explicit Monomial(const std::string&);

    long long coefficient{};
    std::vector<long long> powers{};
};

class Polynomial {
  public:
    explicit Polynomial(const std::string&);

    void print();

    List<Monomial> monomials;
  private:
    int var_c = 0;

    void parse(const std::string&); // Ugh...
};

