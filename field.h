#ifndef FIELD_H
#define FIELD_H

#include <vector>

using namespace std;

class Field
{
private:
    vector<vector<short>> place;

public:
    Field();
    short get_animal(int x, int y);
    void set_animal(int x, int y, short animal);
};

#endif // FIELD_H
