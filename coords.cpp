#include "coords.h"
//Default coordinates constructor
coords::coords() {
    x = 1;
    y = 1;
}
//Parameterized constructor
coords::coords(int x1, int y1) {
    x = x1;
    y = y1;
}
int coords::getX() {
    return x;
}
int coords::getY() {
    return y;
}
//sets the coords
void coords::setCoords(int x1, int y1) {
    x = x1;
    y = y1;
    return;
}