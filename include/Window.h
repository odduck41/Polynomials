#pragma once
#include "../include/DataBase.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <map>
#include <string>

class Window : public QMainWindow {
  Q_OBJECT;
  public:
    explicit Window(QWidget * = nullptr);

    void screen();

  private:
    std::map<std::string, QWidget*> objects;
    QTableWidget* table{};
    // button slots
    void add();
    void remove();
    DataBase dataBase;
};
