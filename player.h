#include "coords.h"
#include <string>
#include <fstream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H
class player {
    private:
        int health;
        coords coordinates;
    public:
        player();
        player(int, int, int);
        player operator = (player const& p) {
            player temp;
            temp.health = p.health;
            temp.coordinates = p.coordinates;
            return temp;
        }
        int getHealth();
        void setHealth(int);
        coords getPlayerCoords();
        void setPlayerCoords(coords);
        void setPlayerCoords(int, int);


};
#endif