#include "player.h"
#include "coords.h"
#include <fstream>
#include <string>
#include <iostream>
#ifndef MAP_H
#define MAP_H
class map {
    private:
        static const int width = 40;
        static const int length = 100;
        std::string file_name;
        char map_grid[width][length];
        player p;
    public:
        map();
        map(std::string, player);
        /* map operator = (map const& temp_m) {
            map m;
            m.file_name = temp_m.file_name;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < length; ++j) {
                    m.map_grid[i][j] = temp_m.map_grid[i][j];
                }
            }
            return m;
        }
        */
        void loadMap();
        std::string returnfile_name();
        void unlocker();
        void setPlayerCoords(int, int);
        char accessTile(int, int);
        void changeName(std::string);
};
#endif //MAP_H