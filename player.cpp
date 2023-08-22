#include "player.h"
//default player constructor
player::player() {
    health = 10;
    coordinates = coords(); //(1,1)
}
//parametrized player constructor
player::player(int h, int x, int y) {
    health = h;
    coordinates = coords(x,y); //(x,y)
}
//returns the health
int player::getHealth() {
    return health;
}
//sets the health
void player::setHealth(int h) {
    health = h;
    return;
}
//returns the x and y coords, respectively
coords player::getPlayerCoords() {
    return coordinates;
}
//sets te coords with coords
void player::setPlayerCoords(coords c) {
    coordinates = c;
    return;
}
//OVERLOAD: sets the coords with an x and y
void player::setPlayerCoords(int x, int y) {
    coordinates.setCoords(x,y);
    return;
}
