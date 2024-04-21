#pragma once
#include "../include/DataBase.h"
#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <map>
#include <string>

class Window : public QMainWindow {
  Q_OBJECT;
  public:
    explicit Window(QWidget * = nullptr);

    void screen();

  private:
    std::map<std::string, QWidget*> objects;
    QListWidget* table{};
    // button slots
    void add();
    void remove();
    void sum();
    DataBase dataBase;
};
