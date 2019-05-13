#include "field.h"
#include <vector>

using namespace std;

Field::Field()
{
    this->place = *new vector<vector<short>>(20, vector<short>(20, 0));
}

short Field::get_animal(int x, int y) {
    if (x < 0 || y < 0 || x > 19 || y > 19) // stackoverflow
        return 0;
    return this->place[x][y];
}

void Field::set_animal(int x, int y, short animal) {
    this->place[x][y] = animal;
}
