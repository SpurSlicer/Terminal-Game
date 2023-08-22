#include "map.h"
//Default constructor (never used)
map::map() {
    int cnt = 0;
    file_name = "sample_map.txt"; //this doesn't exist
    std::ifstream file;
    file.open(file_name); //opens file
    while (!file.eof() && !file.fail()) { //starts loop
    //saves every grid tile
        std::string temp;
        std::getline(file, temp);
        for (int i = 0; i < temp.length(); ++i) {
            map_grid[cnt][i] = temp[i];
        }
        ++cnt;
    }
}
//Parameterized constructor
map::map(std::string s, player op) {
    p = op;
    int cnt = 0;
    std::ifstream file;
    file.open(s);
    while (!file.eof() && !file.fail() && (cnt < width)) {
        //saves every grid tile to map_grid
        std::string temp;
        std::getline(file, temp);
        for (int i = 0; i < length; ++i) {
            map_grid[cnt][i] = temp[i];
        }
        ++cnt;
    }
}
//Prints the map to the console
void map::loadMap() {
    char buffer = map_grid[p.getPlayerCoords().getX()][p.getPlayerCoords().getY()];
    map_grid[p.getPlayerCoords().getX()][p.getPlayerCoords().getY()] = '*';
    bool flag_ground = false;
    bool flag_air = false;
    std::string o = "";
    //main loop
    for (int i = 0; i < width; ++i) {
        if (i != 0) {
            o += "\n";
        }
        //tile type loop
        for (int j = 0; j < length; ++j) {
            if (map_grid[i][j] == '=') { //ground tile
                if (!flag_ground) {
                    flag_air = false;
                    flag_ground = true;
                    o += "\e[0m\e[42m\e[32m";
                }
                o += map_grid[i][j];
            } else if (map_grid[i][j] == ' ') { //air tile
                if (!flag_air) {
                    flag_ground = false;
                    flag_air = true;
                    o += "\e[0m\e[46m";
                }
                o += map_grid[i][j];
            } else if (map_grid[i][j] == '*') { //player tile
                flag_ground = false;
                flag_air = false;
                o += "\e[31m\e[41m";
                o += map_grid[i][j];
            } else if (map_grid[i][j] == '&') { //key tile
                flag_ground = false;
                flag_air = false;
                o += "\e[35m\e[45m";
                o += map_grid[i][j];
            } else if (map_grid[i][j] == '$') {//door tile
                flag_ground = false;
                flag_air = false;
                o += "\e[33m\e[43m";
                o += map_grid[i][j];
            } else if (map_grid[i][j] == '@') {//goal tile
                flag_ground = false;
                flag_air = false;
                o += "\e[95m\e[105m";
                o += map_grid[i][j];
            } else if (map_grid[i][j] == '#') {//spike tile
                flag_ground = false;
                flag_air = false;
                o += "\e[91m\e[101m";
                o += map_grid[i][j];
            } else {
                o += "\e[49m\e[0m";
                std::cout << o << std::endl;
                return;
            }
        }
        flag_ground = false;
        flag_air = false;
    }
    o += "\e[49m\e[0m";
    std::cout << o << std::endl;
    map_grid[p.getPlayerCoords().getX()][p.getPlayerCoords().getY()] = buffer; //this covers the replaced tile from the player addon
    return;
}
//unlocks all doors
void map::unlocker() {
    //checks every tile and replaces door tiles with air tiles
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < length; ++j) {
            if (map_grid[i][j] == '&') {
                map_grid[i][j] = ' ';
            }
            if (map_grid[i][j] == '$') {
                map_grid[i][j] = ' ';
            }
            
        }
    }
    return;
}
//returns file name
std::string map::returnfile_name() {
    return file_name;
}
//sets the x and y coords of a player in a given map
void map::setPlayerCoords(int x, int y) {
    p.setPlayerCoords(x, y);
    return;
}
//returns a tile
char map::accessTile(int x, int y) {
    return map_grid[x][y];
}
//Changes the name of the map and reloads it using the same algorithm in the constructor
void map::changeName(std::string n) {
    file_name = n;
    int cnt = 0;
    std::ifstream file;
    file.open(file_name);
    while (!file.eof() && !file.fail() && (cnt < width)) {
        //SAME ALGORITHM AS CONSTRUCTORS
        std::string temp;
        std::getline(file, temp);
        for (int i = 0; i < length; ++i) {
            map_grid[cnt][i] = temp[i];
        }
        ++cnt;
    }
    return;
}
