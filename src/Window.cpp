#include "../include/Window.h"
#include "../include/Polynomial.h"
#include <QLineEdit>
#include <QHeaderView>
#include <QScrollBar>

Window::Window(QWidget* p) : QMainWindow(p) {
    this->setGeometry({0, 0, 700, 550});
    screen();
}

void Window::screen() {
    table = new QTableWidget(this);
    table->setGeometry({25, 25, 400, 450});
    table->setSelectionMode(QTableWidget::MultiSelection);
    table->setColumnCount(1);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnWidth(0, 900);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

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
}

void Window::add() {
    std::string p = dynamic_cast<QLineEdit*>(objects["input"])->text().toStdString();
    try {
        Polynomial polynomial(p);
        dataBase.insert(polynomial);
        table->setRowCount(table->rowCount() + 1);
        table->setItem(table->rowCount() - 1, 0,
                       new QTableWidgetItem);
        table->item(table->rowCount() - 1, 0)->
                setText(QString::fromStdString((std::string)polynomial));
        table->item(table->rowCount() - 1, 0);
    } catch (std::exception& err) {
        ;
        return;
    }
}

void Window::remove() {
    if (table->rowCount() == 0) return;
    std::vector<size_t> indexes;
    for (int i = 0; i < table->rowCount(); ++i) {
        if (table->item(i, 0)->isSelected()) {
            indexes.emplace_back(i);
        }
    }
    int before = 0;
    for (auto i: indexes) {
        dataBase.erase(i - before);
        before += 1;
    }
    for (auto& i: indexes) {
        if (table->item((int)i, 0) == nullptr) continue;
        table->item((int)i, 0)->setSelected(false);
    }
    before = 0;
    for (auto& i: indexes) {
        for (int j = i - before; j + 1 < table->rowCount(); ++j) {
            table->item(j, 0)->setText(table->item(j + 1, 0)->text());
        }
        before += 1;
    }
    table->setRowCount(table->rowCount() - indexes.size());
}