#include <iostream>
#include "../include/StateMachine.h"
#include "../include/Polynomial.h"
#include "../include/logger.h"

using namespace std;

int main() {
    std::string a;
    getline(cin, a);
//    if (a.empty()) break;
    auto p = Polynomial(a);
    getline(cin, a);
    auto o = Polynomial(a);
    auto e = p + o;
    std::cout << std::string(e);
    Logger final;
    final.close();
}