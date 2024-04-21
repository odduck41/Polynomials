#include "../include/Window.h"
#include <QLineEdit>
#include <QHeaderView>
#include <QScrollBar>

Window::Window(QWidget* p) : QMainWindow(p) {
    this->setGeometry({0, 0, 700, 550});
    screen();
}

void Window::screen() {
    table = new QListWidget(this);
    table->setGeometry({25, 25, 400, 450});
    table->setSelectionMode(QListWidget::MultiSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    const auto input = new QLineEdit(this);
    input->setGeometry({450, 45, 145, 35});
    objects["input"] = input;
    const auto add = new QPushButton(this);
    add->setGeometry({600, 45, 95, 35});
    add->setText("add");
    objects["add"] = add;
    connect(add, &QPushButton::pressed, this, &Window::add);
    const auto remove = new QPushButton(this);
    remove->setGeometry({450, 90, 145 + 95 + 5, 35});
    remove->setText("remove");
    objects["remove"] = remove;
    connect(remove, &QPushButton::pressed, this, &Window::remove);

    const auto sum = new QPushButton(this);
    sum->setGeometry({450, 130, 120, 35});
    sum->setText("+");
    objects["sum"] = sum;
    connect(sum, &QPushButton::pressed, this, &Window::sum);

    const auto composition = new QPushButton(this);
    composition->setGeometry({575, 130, 120, 35});
    composition->setText("*");
    objects["comp"] = composition;
    connect(composition, &QPushButton::pressed, this, &Window::composition);

}

void Window::add() {
    std::string p = dynamic_cast<QLineEdit*>(objects["input"])->text().toStdString();
    try {
        Polynomial polynomial(p);
        dataBase.insert(polynomial);
        table->addItem(QString::fromStdString((std::string)polynomial));
    } catch (std::exception& err) {
        return;
    }
}

void Window::remove() {
    std::vector<int> indexes;
    for (int i = 0; i < table->count(); ++i) {
        if (table->item(i)->isSelected()) {
            indexes.push_back(i);
        }
    }
    int last = 0;
    for (auto& index: indexes) {
        dataBase.erase(index - last);
        ++last;
    }
    last = 0;
    for (auto& index: indexes) {
        auto item = table->takeItem(index - last);
        delete item;
        ++last;
    }
}

void Window::sum() {
    std::vector<int> indexes;
    for (int i = 0; i < table->count(); ++i) {
        if (table->item(i)->isSelected()) {
            indexes.push_back(i);
            table->item(i)->setSelected(false);
        }
    }
    if (indexes.empty()) {
        dynamic_cast<QLineEdit*>(objects["input"])->setText("0");
        return;
    }
    if (indexes.size() == 1) {
        indexes.emplace_back(indexes[0]);
    }
    Polynomial ans;
    for (auto& index: indexes) {
        ans = ans + dataBase[index];
    }
    dynamic_cast<QLineEdit*>(objects["input"])->setText(QString::fromStdString((std::string)ans));
}

void Window::compostion() {
    std::vector<int> indexes;
    for (int i = 0; i < table->count(); ++i) {
        if (table->item(i)->isSelected()) {
            indexes.push_back(i);
            table->item(i)->setSelected(false);
        }
    }
    if (indexes.empty()) {
        dynamic_cast<QLineEdit*>(objects["input"])->setText("0");
        return;
    }
    if (indexes.size() == 1) {
        indexes.emplace_back(indexes[0]);
    }
    Polynomial ans = dataBase[indexes[0]];
    for (int i = 1; i < indexes.size(); ++i) {
        ans = ans * dataBase[indexes[i]];
    }
    dynamic_cast<QLineEdit*>(objects["input"])->setText(QString::fromStdString((std::string)ans));
}