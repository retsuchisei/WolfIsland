#include "wolf.h"
#include "field.h"
#include "rabbit.h"
#include <QtGlobal>
#include <vector>
#include <iterator>

Wolf::Wolf(int x, int y)
{
    this->gender = qrand() % 2;
    this->health = 1.0;
    this->x = x;
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

vector<Rabbit>::iterator find_rabbit(int x, int y, vector<Rabbit> rabbits) {
    for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        if ( (*it).get_x() == x && (*it).get_y() == y)
            return it;
    }
}

vector<Wolf>::iterator find_she_wolf(int x, int y, vector<Wolf> wolfs) {
    for (auto it = wolfs.begin(); it != wolfs.end(); ++it) {
        if ( (*it).get_x() == x && (*it).get_y() == y && (*it).get_gender() == 0)
            return it;
    }
}

void Wolf::move(Field field, vector<Wolf> wolfs, vector<Rabbit> rabbits) {
    field.set_animal(this->x, this->y, 0);
    bool hungry = 1;
    for (int i = this->x - 1; i < i + 2; ++i) {
        for (int j = this->y - 1; j < j + 2; ++j)
            if (field.get_animal(i, j) == 3) {
                auto it = find_she_wolf(i, j, wolfs);
                wolfs.push_back(Wolf((*it).get_x(), (*it).get_y()));
                hungry = 0;
                break;
            }
        if (!hungry)
            break;
    }
    if (this->gender == 1 && hungry) {
        for (int i = this->x - 1; i < i + 2; ++i) {
            for (int j = this->y - 1; j < j + 2; ++j)
                if (field.get_animal(i, j) == 1) {

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
    }
    if (this->get_gender() == 1)
        field.set_animal(this->x, this->y, 1); // wolf
    else
        field.set_animal(this->x, this->y, 3); // she-wolf

}
