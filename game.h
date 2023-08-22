#include "player.h"
#include "map.h"
#include "coords.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#ifndef GAME_H
#define GAME_H
class game {
    private:
        const std::string menubar = "=============================================Game Time=============================================";
        const std::string healthbar = "\e[49m\e[0m\e[41mHealth:\e[49m";
        const std::string weaponsbar = "\e[49m\e[0m\e[44mItems:\e[49m";
        const std::string boarder = "===================================================================================================";
        map current_map;
        int RIGHT = 77, LEFT = 75, UP = 72, DOWN = 80, ESC = 27, MENU = 113;
        std::string player_name = "player";
        map pause_map = map("pause.txt", op);
        std::string name_of_map; 
        std::vector<std::string> infobar;
        player op;
        std::string collectibles = "0";
        int progress = 1;
    public:
        game();
        game(std::string, player);
        player accessPlayer();
        void updatePlayerCoords(int, int);
        std::string accessMapName();
        void setMap(std::string);
        void consoleAdd(std::string);
        void consolePrint();
        void refresh();
        void closeGame();
        bool save();
        void clearSave();
        void hub();
        bool coordsChecker(int, int, char);
        void unlockerForMap();
        void pauseLoad();
        void pause();
        int getRight();
        int getLeft();
        int getUp();
        int getDown();
        int getEsc();
        int getMenu();
        void updateFromSave();
        bool goalFinder();
        void goal();
        std::string getProgress();
        bool damage();
        void addCollectible(std::string);
        std::string printCollectibles();
};
#endif //GAME_H