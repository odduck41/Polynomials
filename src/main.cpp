#include <iostream>
#include "../include/StateMachine.h"
#include "../include/Polynomial.h"
#include "../include/logger.h"
#include "../include/Window.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    Window window;
    window.show();
    return QApplication::exec();
}