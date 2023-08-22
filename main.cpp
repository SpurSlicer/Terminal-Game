#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> //Used for auto fullscreen
#include <vector>
#include <conio.h> //Used for instant input (_getch())
#include "game.h"
#include "map.h"
#include "player.h"
#include "coords.h"
//using namespace std;
//WINDOWS ONLY algo that forceably makes the terminal full screen
void AltEnter()
{
    //this activates "alt + enter" which makes the terminal fullscreen
    keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}
//This helper function enables color, fullscreens the terminal, and outputs a message to the player 
void setUpWindow() {
    //Enables fullscreen by default
    AltEnter();
    //Enables color
    system("color");
    std::cout << "Press any key to begin!" << std::endl; //so far so good. time to start!
    _getch();
    system("cls");
    return;
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------*/
int main() {
    setUpWindow();
restart: //if the player dies, jump here
    player op; //you, the player
    op.setHealth(10); //sets health to the default (10)
    game g = game("Level_1.txt", op); //loads level 1 with the player
    g.updateFromSave(); //updates everything in case a save file is detected
    g.refresh(); //loads everything


//while the player is giving inputs, do the following:
    while (char input = _getch()) {
//RIGHT ARROW
            if(input == g.getRight()) { 
                if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()+1, '@'))  { //is the player on a goal?
                    std::string resp = "Level ";
                    resp += g.getProgress();
                    resp += " Complete!";
                    g.goal();
                } if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()+1, '#'))  { //did the player hit a spike?
                    if (g.damage()) {
                        system("cls");
                        goto restart;
                    } else {
                        g.refresh();
                    }
                    //checks if the player runs into a wall or a door
                } else if ((!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()+1, '='))) && (!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()+1, '$')))) {
                    op.setPlayerCoords(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()+1);
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.refresh();
                    //checks if the player hits a key
                } if ((g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY(), '&'))) {
                    g.unlockerForMap();
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.consoleAdd("Key has been picked up! Progress to the Goal!");
                    g.refresh();
                }
//LEFT ARROW
            } else if (input == g.getLeft()) {
                if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()-1, '@'))  { //did the player run into a goal?
                    std::string resp = "Level ";
                    resp += g.getProgress();
                    resp += " Complete!";
                    g.consoleAdd(resp);
                    g.goal();
                } if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()-1, '#'))  { //did the player run into a spike?
                    if (g.damage()) {
                        system("cls");
                        goto restart;
                    } else {
                        g.refresh();
                    }
                    //checks if the player runs into a door or wall
                } else if ((!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()-1, '='))) && (!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()-1, '$')))) {
                    op.setPlayerCoords(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY()-1);
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.refresh();
                    //checks if the player runs into a key
                } if ((g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY(), '&'))) {
                    g.unlockerForMap();
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.consoleAdd("Key has been picked up! Progress to the Goal!");
                    g.refresh();
                }
//UP ARROW
            } else if (input == g.getUp()) {
                if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()-1, g.accessPlayer().getPlayerCoords().getY(), '@'))  { //did the player run into a goal?
                    std::string resp = "Level ";
                    resp += g.getProgress();
                    resp += " Complete!";
                    g.consoleAdd(resp);
                    g.goal();
                } if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()-1, g.accessPlayer().getPlayerCoords().getY(), '#'))  { //did the player run into a spike?
                    if (g.damage()) {
                        system("cls");
                        goto restart;
                    } else {
                        g.refresh();
                    }
                    //checks if the player runs into a wall or door
                } else if ((!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()-1, g.accessPlayer().getPlayerCoords().getY(), '='))) && (!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()-1, g.accessPlayer().getPlayerCoords().getY(), '$')))) {
                    op.setPlayerCoords(g.accessPlayer().getPlayerCoords().getX()-1, g.accessPlayer().getPlayerCoords().getY());
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.refresh();
                    //checks if the player runs into a key
                } if ((g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY(), '&'))) {
                    g.unlockerForMap();
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.consoleAdd("Key has been picked up! Progress to the Goal!");
                    g.refresh();
                }
//DOWN ARROW
            } else if (input == g.getDown()) {
                if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()+1, g.accessPlayer().getPlayerCoords().getY(), '@'))  { //did the player run into a goal?
                    std::string resp = "Level ";
                    resp += g.getProgress();
                    resp += " Complete!";
                    g.consoleAdd(resp);
                    g.goal();
                } if (g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()+1, g.accessPlayer().getPlayerCoords().getY(), '#'))  { //did the player run into a spike?
                    if (g.damage()) {
                        system("cls");
                        goto restart;
                    } else {
                        g.refresh();
                    }
                    //checks if the player runs into a wall or door
                } else if ((!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()+1, g.accessPlayer().getPlayerCoords().getY(), '='))) && (!(g.coordsChecker(g.accessPlayer().getPlayerCoords().getX()+1, g.accessPlayer().getPlayerCoords().getY(), '$')))) {
                    op.setPlayerCoords(g.accessPlayer().getPlayerCoords().getX()+1, g.accessPlayer().getPlayerCoords().getY());
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.refresh();
                    //checks if the player runs into a key
                } if ((g.coordsChecker(g.accessPlayer().getPlayerCoords().getX(), g.accessPlayer().getPlayerCoords().getY(), '&'))) {
                    g.unlockerForMap();
                    g.updatePlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY());
                    g.consoleAdd("Key has been picked up! Progress to the Goal!");
                    g.refresh();
                }
//ESCAPE KEY
            } else if (input == g.getEsc()) {
                    exit(0); //exits program
//EXIT KEY
            }else if (input == g.getMenu()) {
                    g.pause(); //opens pause menu
                    g.refresh();
            }
        }
    return 0; //never reached
}