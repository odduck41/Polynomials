#include "../include/StateMachine.h"

#define IGNORE

bool stateMachine(const std::string& s, size_t i, int state) {
    if (i == s.size()) {
        if (state == 2) {
            throw string_error((std::string) "Polynomial ends with operator " + s[i - 1] + ", string = «" + s + "»");
        }
        if (state == 3) {
            throw string_error("Polynomial ends with operator ^, string = «" + s + "»");
        }
        return true;
    }
    char a = s[i];
#ifdef IGNORE
    if (a == ' ') {
        return stateMachine(s, i + 1, state);
    }
#endif
    switch (state) {
        case -1:
            if ('0' <= a && a <= '9') {
                return stateMachine(s, i + 1, 0);
            } else if ('a' <= a && a <= 'z') {
                return stateMachine(s, i + 1, 1);
            } else if (a == '+' || a == '-') {
                return stateMachine(s, i + 1, 2);
            }
            throw string_error("Incorrect symbol in position 0, string = «" + s + "»");
        case 0:
            if ('0' <= a && a <= '9') {
                return stateMachine(s, i + 1, 0);
            } else if ('a' <= a && a <= 'z') {
                return stateMachine(s, i + 1, 1);
            } else if (a == '+' || a == '-') {
                return stateMachine(s, i + 1, 2);
            }
            throw string_error("Incorrect symbol in position " + std::to_string(i) + ", string = «" + s + "»");
        case 1:
            if ('a' <= a && a <= 'z') {
                return stateMachine(s, i + 1, 1);
            } else if (a == '+' || a == '-') {
                return stateMachine(s, i + 1, 2);
            } else if (a == '^') {
                return stateMachine(s, i + 1, 3);
            }
            throw string_error("Incorrect symbol in position " + std::to_string(i) + ", string = «" + s + "»");
        case 2:
            if ('0' <= a && a <= '9') {
                return stateMachine(s, i + 1, 0);
            } else if ('a' <= a && a <= 'z') {
                return stateMachine(s, i + 1, 1);
            }
            throw string_error("Incorrect symbol in position " + std::to_string(i) + ", string = «" + s + "»");
        case 3:
            if ('0' <= a && a <= '9') {
                return stateMachine(s, i + 1, 0);
            }
            throw string_error("Incorrect symbol in position " + std::to_string(i) + ", string = «" + s + "»");
        default:
            throw Devil("Error"); // I pray(know) it will never throw
    }
//    throw Devil("If this shit happen, I will die from cringe");
}
