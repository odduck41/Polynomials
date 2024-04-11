#include <iostream>
#include "../include/StateMachine.h"
#include "../include/Polynomial.h"
#include "../include/logger.h"

using namespace std;

int main() {
    std::string a;
    while (!cin.eof()) {
        getline(cin, a);
        if (a.empty()) break;
        auto p = Polynomial(a);
        p.print();
    }
    Logger final;
    final.close();
}