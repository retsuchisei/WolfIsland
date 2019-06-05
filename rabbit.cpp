#include "rabbit.h"
#include "field.h"
#include <vector>
#include <QtGlobal>
#include <QObject>
#include <QDateTime>
#include <QDebug>

using namespace std;

Rabbit::Rabbit(int x, int y)
{
    if (x > 19 || x < 0)
        this->x = 0;
    else
        this->x = x;
    if (y > 19 || y < 0)
        this->y = 0;
    else
        this->y = y;
}

void Rabbit::set_x(int x) {
    this->x = x;
}

void Rabbit::set_y(int y) {
    this->y = y;
}

int Rabbit::get_x() {
    return this->x;
}

int Rabbit::get_y() {
    return this->y;
}

void Rabbit::move(Field * field, vector<Rabbit> * rabbits) {
    qsrand(QDateTime::currentMSecsSinceEpoch());
    if (qrand() % 10 < 2 && rabbits->size() < 50)
        rabbits->push_back(Rabbit(this->x, this->y));
    if (this->x > 19 || this->x < 0 || this->y > 19 || this->y < 0) {
        this->y = 0;
        this->x = 0;
    }
    field->set_animal(this->x, this->y, 0);
    int go = qrand() % 9;
    if ((go == 8 || go == 1 || go == 2) && this->y != 19) // move down
        this->set_y(this->y + 1);

    if ((go == 6 || go == 5 || go == 4) && this->y != 0) // move up
        this->set_y(this->y - 1);

    if ((go == 4 || go == 3 || go == 2) && this->x != 19) // move right
        this->set_x(this->x + 1);

    if ((go == 6 || go == 7 || go == 8) && this->x != 0) // move left
        this->set_x(this->x - 1);
    if (this->x > 19 || this->x < 0 || this->y > 19 || this->y < 0) {
        this->y = 0;
        this->x = 0;
    }
    field->set_animal(this->x, this->y, 2); // 2 number = rabbit

}
