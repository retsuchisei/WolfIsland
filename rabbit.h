#ifndef RABBIT_H
#define RABBIT_H

#include <vector>
#include "field.h"

class Rabbit
{
private:
    int x, y;

public:
    Rabbit(int x, int y);
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
    void move(Field field, vector<Rabbit> rabbits);
};

#endif // RABBIT_H
