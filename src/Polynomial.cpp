#include "../include/Polynomial.h"
#include "../include/StateMachine.h"
#include "../include/logger.h"

Monomial::Monomial(const std::string& term) {
    powers.resize(26);
    // Firstly we parse coefficient
    // Parse var. If after var name ^ parse next number, else powers[var] += 1
    bool coefficient_phase = true;
    std::string c;
    for (auto i = 0ull; i < term.size(); ++i) {
        while (coefficient_phase && i < term.size() && (term[i] == '-' || ('0' <= term[i] && term[i] <= '9'))) {
            c += term[i++];
        }
        if (coefficient_phase && c.empty()) {
            coefficient = 1;
            coefficient_phase = false;
        } else if (coefficient_phase && c == "-") {
            coefficient = -1;
            coefficient_phase = false;
        } else if (coefficient_phase) {
            try {
                coefficient = stoll(c);
            } catch (std::exception& err) {
                Logger a;
                a << (std::string)err.what();
            }
            coefficient_phase = false;
        }
        if ('a' <= term[i] && term[i] <= 'z') {
            if (i + 1 < term.size() && term[i + 1] == '^') {
                auto var_index = i;
                i += 2;
                auto power = 0ll;
                while (i < term.size() && term[i] < 'a') {
                    power *= 10;
                    power += (term[i++] - '0');
                }
                powers[term[var_index] - 'a'] += power;
                --i;
            } else {
                powers[term[i] - 'a'] += 1;
            }
        }
    }
}

bool Monomial::operator<(const Monomial& other) {
    for (int i = 0; i < 26; ++i) {
        if (powers[i] < other.powers[i]) return true;
        else if (powers[i] > other.powers[i]) return false;
    }
    return coefficient < other.coefficient;
}

void Polynomial::normalize() {
    for (size_t i = 0; i < monomials.size();) {
        for (auto j = i + 1; j < monomials.size();) {
            bool eq = true;
            for (int f = 0; f < 26; ++f) {
                if (monomials[i].powers[f] != monomials[j].powers[f]) {
                    eq = false;
                }
            }
            if (eq) {
                monomials[i].coefficient += monomials[j].coefficient;
                monomials.erase(j);
                continue;
            }
            ++j;
        }
        if (monomials[i].coefficient == 0) {
            monomials.erase(i);
            continue;
        }
        ++i;
    }
    var_c = 0;
    for (size_t i = 0; i < monomials.size(); ++i) {
        int vars = 0;
        for (auto& var: monomials[i].powers) {
            if (var) {
                ++vars;
            }
        }
        var_c = std::max(var_c, vars);
    }
    sort();
}

Polynomial::Polynomial(const std::string& expression) {
    std::string expr; // with removed spaces
    for (auto& letter: expression) {
        if (letter != ' ') expr += letter;
    }
    Logger a;
    a << (std::string)"Received expression: «" + expr + "»";
    try {
        stateMachine(expr);
    } catch(Devil& err) {
        a << (std::string)"Error occured! " + (std::string)err.what();
        throw err;
    } catch (string_error& err) {
        Logger b;
        b << (std::string)"Error occured! " + (std::string)err.what();
        throw err;
    } catch (std::exception& err) {
        a << (std::string)"Some error occured, idk what is this: " + err.what();
        throw err;
    }
    parse(expr);
    normalize();
}

void Polynomial::parse(const std::string& expression) {
    std::string now;
    for (auto& letter: expression) {
        if (letter == '+') {
            monomials.insert(Monomial(now));

            now = {};
            continue;
        }
        if (letter == '-') {
            monomials.insert(Monomial(now));
            now = "";
        }
        now += letter;
    }
    monomials.insert(Monomial(now));

}

Polynomial::operator std::string() const {
    std::string answer;
    for (int i = 0; i < monomials.size(); ++i) {
        bool flag = false;
        for (auto& j: monomials[i].powers) {
            if (j != 0) flag = true;
        }
        if (monomials[i].coefficient == 1 && !flag) {
            if (i != 0) {
                answer += "+";
            }
            answer += "1";
        } else if (monomials[i].coefficient == -1 && flag) {
            answer += "-";
        } else if (monomials[i].coefficient > 0 && monomials[i].coefficient != 1) {
            if (i != 0) {
                answer += "+";
            }
            answer += std::to_string(monomials[i].coefficient);
        } else if (monomials[i].coefficient < 0) {
            answer += std::to_string(monomials[i].coefficient);
        } else if (monomials[i].coefficient == 1) {
            if (i != 0) {
                answer += "+";
            }
        }
        for (int j = 0; j < 26; ++j) {
            if (monomials[i].powers[j] != 0) {
                answer += char(j + 'a');
                if (monomials[i].powers[j] != 1) {
                    answer += "^" + std::to_string(monomials[i].powers[j]);
                }
            }
        }
    }
    if (answer.empty()) {
        answer = "0";
    }
    return answer;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial answer;
    for (int i = 0; i < monomials.size(); ++i) {
        answer.monomials.insert(monomials[i]);
    }
    for (int i = 0; i < other.monomials.size(); ++i) {
        answer.monomials.insert(other.monomials[i]);
    }
    answer.normalize();
    return answer;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial answer;
    for (size_t i = 0; i < other.monomials.size(); ++i) {
        for (size_t j = 0; j < monomials.size(); ++j) {
            Monomial x;
            x.powers = other.monomials[i].powers;
            x.coefficient = other.monomials[i].coefficient;
            x.coefficient *= monomials[j].coefficient;
            for (int k = 0; k < 26; ++k) {
                x.powers[k] += monomials[j].powers[k];
            }
            answer.monomials.insert(x);
        }
    }
    answer.normalize();
    return answer;
}

void Polynomial::sort() const {
    for (int i = 0; i < monomials.size(); ++i) {
        for (int j = i + 1; j < monomials.size(); ++j) {
            if (monomials[i] < monomials[j]) {
                std::swap(monomials[i].coefficient, monomials[j].coefficient);
                std::swap(monomials[i].powers, monomials[j].powers);
            }
        }
    }
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (other.monomials.size() != monomials.size()) return false;
    for (int i = 0; i < monomials.size(); ++i) {
        if (monomials[i].coefficient != other.monomials[i].coefficient) {
            return false;
        }
        for (int j = 0; j < 26; ++j) {
            if (monomials[i].powers[j] != other.monomials[i].powers[j]) {
                return false;
            }
        }
    }
    return true;
}


