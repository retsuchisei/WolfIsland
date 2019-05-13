#include "mainwindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QtDebug>
#include "field.h"
#include "rabbit.h"
#include "wolf.h"
#include <vector>
#include <iterator>

void start(Field field, vector<Wolf> wolfs, vector<Rabbit> rabbits) {
    int x, y;

    for (int i = 0; i < 3; ++i) {
        do {
            x = qrand() % 20;
            y = qrand() % 20;
        } while (field.get_animal(x, y) != 0);
        wolfs.push_back(Wolf(x, y));
    }
    for (int i = 0; i < 3; ++i) {
        do {
            x = qrand() % 20;
            y = qrand() % 20;
        } while (field.get_animal(x, y) != 0);
        rabbits.push_back(Rabbit(x, y));
    }
}

void move_rabbits(Field field, vector<Rabbit> rabbits) {
    for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        (*it).move(field, rabbits);
    }
}

void move_wolfs(Field field, vector<Wolf> wolfs, vector<Rabbit> rabbits) {
    for (auto it = wolfs.begin(); it != wolfs.end(); ++it) {
        (*it).move(field, wolfs, rabbits);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Field field = Field();
    vector<Wolf> wolfs;
    vector<Rabbit> rabbits;

    start(field, wolfs, rabbits);

    while (1) {
        move_rabbits(field, rabbits);
        move_wolfs(field, wolfs, rabbits);
        if (1)
            break;
    }

    return a.exec();
}
