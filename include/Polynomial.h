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
    bool operator<(const Monomial&);
};

class Polynomial {
  public:
    Polynomial() = default;
    explicit Polynomial(const std::string&);

    explicit operator std::string() const;
    List<Monomial> monomials;
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
  private:
    int var_c = 0;
    void normalize();
    void parse(const std::string&); // Ugh...
    void sort() const;
};

