#include "wolf.h"
#include "field.h"
#include "rabbit.h"
#include <QtGlobal>
#include <QDateTime>
#include <QDebug>
#include <vector>
#include <iterator>

Wolf::Wolf(int x, int y)
{
    this->gender = qrand() % 2;
    this->health = 1.0;

    if (x > 19 || x < 0)
        this->x = 0;
    else
        this->x = x;
    if (y > 19 || y < 0)
        this->y = 0;
    else
        this->y = y;
}

void Wolf::set_x(int x) {
    this->x = x;
}

void Wolf::set_y(int y) {
    this->y = y;
}

void Wolf::set_health(float health) {
    this->health = health;
}

int Wolf::get_x() {
    return this->x;
}

int Wolf::get_y() {
    return this->y;
}

float Wolf::get_health() {
    return this->health;
}

bool Wolf::get_gender() {
    return this->gender;
}

int find_rabbit(int x, int y, vector<Rabbit> rabbits) {
    int i = 0;
    for (i; i < rabbits.size(); ++i) {
        if (rabbits[i].get_x() == x && rabbits[i].get_y() == y)
            break;
    }
    return i < rabbits.size() ? i : -1;
}

int find_she_wolf(int x, int y, vector<Wolf> wolfs) {
    int i = 0;
    for (i; i < wolfs.size(); ++i) {
        if (wolfs[i].get_x() == x && wolfs[i].get_y() == y && wolfs[i].get_gender() == 0)
            break;
    }
    return i < wolfs.size() ? i : -1;
}

void Wolf::move(Field * field, vector<Wolf> * wolfs, vector<Rabbit> * rabbits, std::vector<Wolf>::iterator wolf) {
    qsrand(int(QDateTime::currentMSecsSinceEpoch()));
    field->set_animal(this->x, this->y, 0);
    bool hungry = 1;
    for (int i = this->x - 1; i < this->x + 2; ++i) {
        for (int j = this->y - 1; j < this->y + 2; ++j)
            if (field->get_animal(i, j) == 2) {
                auto it = find_rabbit(i, j, *rabbits);
                rabbits->erase(rabbits->begin() + it);

                field->set_animal(i, j, 0);
                this->health += 1.0f; // Added 1 health point (- 1 rabbit(eated))
                hungry = 0;
                break;
            }
        if (!hungry)
            break;
    }
    if (this->gender == 1 && hungry && wolfs->size() < 50) {
        for (int i = this->x - 1; i < this->x + 2; ++i) {
            for (int j = this->y - 1; j < this->y + 2; ++j)
                if (field->get_animal(i, j) == 3) {
                    wolfs->push_back(Wolf(this->get_x(), this->get_y()));
                    hungry = 0;
                    break;
                }
            if (!hungry)
                break;
        }
    }
    if (hungry) {
        int go = qrand() % 9;
        if ((go == 8 || go == 1 || go == 2) && this->y != 19) // move down
            this->set_y(this->y + 1);

        if ((go == 6 || go == 5 || go == 4) && this->y != 0) // move up
            this->set_y(this->y - 1);

        if ((go == 4 || go == 3 || go == 2) && this->x != 19) // move right
            this->set_x(this->x + 1);

        if ((go == 6 || go == 7 || go == 8) && this->x != 0) // move left
            this->set_x(this->x - 1);
        this->health -= 0.1f;
    }

    //qDebug() << "Wolf " << this->health;

    if (this->health < 0.1f) {
        field->set_animal(this->x, this->y, 0); // wolf is dead!
        wolfs->erase(wolf);
        return;
    }

    if (this->get_gender() == 1)
        field->set_animal(this->x, this->y, 1); // wolf
    else
        field->set_animal(this->x, this->y, 3); // she-wolf

}
