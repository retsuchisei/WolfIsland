#ifndef WOLF_H
#define WOLF_H

#include "field.h"
#include "rabbit.h"
#include <vector>

class Wolf
{
private:
    bool gender;
    float health;
    int x, y;

public:
    Wolf(int x, int y);
    void set_x(int x);
    void set_y(int y);
    void set_health(float health);
    int get_x();
    int get_y();
    float get_health();
    bool get_gender();
    void move(Field field, vector<Wolf> wolfs, vector<Rabbit> rabbits);

};

#endif // WOLF_H
