#pragma once

#include <QMainWindow>
#include <map>
#include <string>

class Window : public QMainWindow {
  Q_OBJECT;
  public:
    explicit Window(QWidget * = nullptr);

    void screen();

  private:
    std::map<std::string, QWidget> objects;
};
