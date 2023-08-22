#include "game.h"
#include <conio.h>
//Default constructor
game::game() {
    op = player();
    current_map = map();
}
//Parameterized constructor
game::game(std::string m, player p) {
    op = p;
    current_map = map(m, p);
}
//returns the player object
player game::accessPlayer() {
    return op;
}
//changes the coordinates of the player
void game::updatePlayerCoords(int x, int y) {
    op.setPlayerCoords(x,y);
    return;
}
//returns the given name of the current map
std::string game::accessMapName() {
    return current_map.returnfile_name();
}
//adds a new map
void game::setMap(std::string m) {
    current_map = map(m, op);
    return;
}
//adds some text to the console (the commentary below the map)
void game::consoleAdd(std::string s) {
    //if the infobar vector has a size greater than 5, it replaces the last item and adds the new item in the first spot, pushing everything else back
    if (infobar.size() == 5) {
        infobar.erase(infobar.begin());
    }
    infobar.push_back(s);
    return;
}
//prints the contents of the console
void game::consolePrint() {
    std::string buffer = "";
    int cnt = 0;
    //prints each element in the console
    for (std::string i : infobar) {
        if (cnt < infobar.size()-1) {
            buffer += i;
            buffer += "\n";
        } else {
            buffer += i;
        }
    }
    std::cout << buffer << std::endl;

}
/* CRUCIAL ALGORITHM
* This is responsible for rendering the entire map
* It begins by rendering each boarder = sign in a rainbow color
* It then prints all of the stats of the current player (op)
* It then loads another boarder with the same algorithm as before
* Next, it loads the entire map using the algorithm from the map class
* It then loads another boarder
* It finishes by loading the console
*/
void game::refresh() {
    std::string win = "";
    int cnt = 0;
    //rainbow color boarder sign algorithm
    for (int i = 0; i < menubar.length(); ++i) {
        if (menubar[i] == '=') {
            if (cnt == 0) {
                win += "\e[31m";
                win += menubar[i]; 
                ++cnt;
            } else if (cnt == 1) {
                win += "\e[33m";
                win += menubar[i];
                ++cnt;
            } else if (cnt == 2) {
                win += "\e[32m";
                win += menubar[i];
                ++cnt;
            } else if (cnt == 3) {
                win += "\e[36m";
                win += menubar[i];
                ++cnt;            
            } else if (cnt == 4) {
                win += "\e[34m";
                win += menubar[i];
                ++cnt;
            } else if (cnt == 5) {
                win += "\e[35m";
                win += menubar[i];
                cnt = 0;
            }
        } else {
            win += "\e[0m";
            win += menubar[i];
            cnt = 0;
        }
    }
    //prints all of the stats
    win += "\e[49m\e[0m";
    win += "\n";
    win += player_name;
    win += "\n";
    win += healthbar;
    win +=  " \e[49m\e[0m";
    win += std::to_string(op.getHealth());
    win += "\n";
    win += weaponsbar;
    win += " ";
    win += collectibles;
    win += "\n";
    cnt = 0;
    //loads rainbow boarder again
    for (int i = 0; i < boarder.length(); ++i) {
        if (boarder[i] == '=') {
            if (cnt == 0) {
                win += "\e[31m";
                win += boarder[i]; 
                ++cnt;
            } else if (cnt == 1) {
                win += "\e[33m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 2) {
                win += "\e[32m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 3) {
                win += "\e[36m";
                win += boarder[i];
                ++cnt;            
            } else if (cnt == 4) {
                win += "\e[34m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 5) {
                win += "\e[35m";
                win += boarder[i];
                cnt = 0;
            }
        } else {
            win += "\e[0m";
            win += menubar[i];
            cnt = 0;
        }
    }
    //clears system and prints the stats board
    system("cls");
    std::cout << win << std::endl;
    win = "";
    current_map.setPlayerCoords(op.getPlayerCoords().getX(), op.getPlayerCoords().getY()); //sets player coords for map rendering
    current_map.loadMap(); //loads the map in the map slot
    cnt = 0;
    //algorithm for loading another rainbow boarder below the map
    for (int i = 0; i < boarder.length(); ++i) {
        if (boarder[i] == '=') {
            if (cnt == 0) {
                win += "\e[31m";
                win += boarder[i]; 
                ++cnt;
            } else if (cnt == 1) {
                win += "\e[33m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 2) {
                win += "\e[32m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 3) {
                win += "\e[36m";
                win += boarder[i];
                ++cnt;            
            } else if (cnt == 4) {
                win += "\e[34m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 5) {
                win += "\e[35m";
                win += boarder[i];
                cnt = 0;
            }
        } else {
            win += "\e[0m";
            win += boarder[i];
            cnt = 0;
        }
    }
    //prints the map and prints the console
    std::cout << win << "\e[0m\n";
    consolePrint();
    return;
}
//calls system exit code 0 to close the game (unused)
void game::closeGame() {
    exit(0);
}
//saves the health, name, progress, and collectibles to data.txt (self explanatory algo)
bool game::save() {
    std::ofstream saveData;
    saveData.open("data.txt"); 
    if (saveData.fail()) {
        return false;
    } else {
        saveData << op.getHealth() << std::endl;
        saveData << player_name << std::endl;
        saveData << progress << std::endl;
        saveData << collectibles << std::endl;
        saveData.close();
        return true;
    }
}
//Truncates the file and clears all data, thus erasing the save
void game::clearSave() {
    std::ofstream saveData;
    saveData.open("data.txt", std::ofstream::out | std::ofstream::trunc); //this clears the file
    saveData.close();
    return;
}
//compares a tiletype c to the given coordinates (x,y)
bool game::coordsChecker(int x, int y, char c) {
    if (c == current_map.accessTile(x,y)) {
        return true;
    } else {
        return false;
    }
}
//unlocks all doors for the current map
void game::unlockerForMap() {
    current_map.unlocker();
    return;
}
/* ALGORITHM (crucial)
* This loads the entire pause screen
* It begins by calling the same rainbow boarder algorithm
* It then loads the special pause map that does not allow player movement
* It finishes by calling another rainbow boarder
*/
void game::pauseLoad() {
    int cnt = 0;
    std::string win = "";
    //stores rainbow boarder in win
    for (int i = 0; i < boarder.length(); ++i) {
        if (boarder[i] == '=') {
            if (cnt == 0) {
                win += "\e[31m";
                win += boarder[i]; 
                ++cnt;
            } else if (cnt == 1) {
                win += "\e[33m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 2) {
                win += "\e[32m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 3) {
                win += "\e[36m";
                win += boarder[i];
                ++cnt;            
            } else if (cnt == 4) {
                win += "\e[34m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 5) {
                win += "\e[35m";
                win += boarder[i];
                cnt = 0;
            }
        } else {
            win += "\e[0m";
            win += boarder[i];
            cnt = 0;
        }
    }
    system("cls");
    std::cout << win << std::endl; //prints the boarder
    pause_map.loadMap(); //loads the special pause map below
    cnt = 0;
    win = "";
    //prints yet another rainbow boarder
    for (int i = 0; i < boarder.length(); ++i) {
        if (boarder[i] == '=') {
            if (cnt == 0) {
                win += "\e[31m";
                win += boarder[i]; 
                ++cnt;
            } else if (cnt == 1) {
                win += "\e[33m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 2) {
                win += "\e[32m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 3) {
                win += "\e[36m";
                win += boarder[i];
                ++cnt;            
            } else if (cnt == 4) {
                win += "\e[34m";
                win += boarder[i];
                ++cnt;
            } else if (cnt == 5) {
                win += "\e[35m";
                win += boarder[i];
                cnt = 0;
            }
        } else {
            win += "\e[0m";
            win += boarder[i];
            cnt = 0;
        }
    }
}
/* ALGORITHM (crucial)
* Starts by utilizing a vector to store the 7 settings options
* It then opens up a large switch case statement that alternates through the given settings (check down below for discritions)
* This will loop until further action is takin
*/
void game::pause() {
    system("cls");
    //this vector below stores the settings options
    std::vector<std::string> information = {"1. Controls", "2. Save", "3. Surprise Level", "4. Rename Character","5. Quit", "6. Clear Save", "Escape to Continue Playing"};
    std::string new_name = "";
    pauseLoad();
    //for range loop prints every settings option to the pause console
    for (auto i : information) {
        std::cout << i << std::endl;
    }
    while (char input = _getch()) {
        switch (input) {
            case '1': //controls
            //This modifies every control used by the game
                system("cls");
                pauseLoad();
                std::cout << "Enter your RIGHT DIRECTION key: ";
                RIGHT = _getch();
                system("cls");
                pauseLoad();
                std::cout << "Enter your LEFT DIRECTION key: ";
                LEFT = _getch();
                system("cls");
                pauseLoad();
                std::cout << "Enter your UP DIRECTION key: ";
                UP = _getch();
                system("cls");
                pauseLoad();
                std::cout << "Enter your DOWN DIRECTION key: ";
                DOWN = _getch();
                system("cls");
                pauseLoad();
                std::cout << "Enter your EXIT GAME key: ";
                ESC = _getch();
                system("cls");
                pauseLoad();
                std::cout << "Enter your MENU key: ";
                MENU = _getch();
                system("cls");
                goto end;
                break;
            case '2': //save
            //this just saves the game
                save();
                system("cls");
                pauseLoad();
                std::cout << "Game saved. (press a key to continue)";
                _getch();
                system("cls");
                goto end;
                break;
            case '3': //random level
            //this uses a random number generator to send the player to a random level (1-5)
                system("cls");
                pauseLoad();
                srand((unsigned)time(0));
                int number;
                number = rand() % 5 + 1;
                std::cout << "Press any key to start level " << number << "!";
                name_of_map = "Level_";
                name_of_map += std::to_string(number);
                name_of_map += ".txt";
                op.setPlayerCoords(1,1);
                current_map.changeName(name_of_map);
                _getch();
                system("cls");
                goto end;
                break;
            case '4': //rename character
            //this prompts the player to enter a name for their character. This value can be saved
                system("cls");
                pauseLoad();
                std::cout << "Enter the name: ";
                std::getline(std::cin, new_name);
                player_name = new_name;
                system("cls");
                goto end;
                break;
            case '5': //exit
            //exits the entire program
                exit(0);
                break;
            case '6': //clear save
            //this gives you the option to clear your save or not.
                char response;
                system("cls");
                pauseLoad();
                std::cout << "Are you sure you want to erase your save data? (y/n)" << std::endl;
                //loop prompts the player for a double check (clearing a save is a big deal)
                while (response = _getch()) {
                    switch (response) {
                        case 'y': //yes
                            clearSave();
                            system("cls");
                            goto end;
                        case 'n': //no
                            pause();
                            break;
                    }
                }
                
            case '\e': //return to game
            //escape just makes the player return to the game
                refresh();
                goto end;
                break;
        }
    }
end:
    return;
}
//The direction algos are self explanatory
int game::getRight() {
    return RIGHT;
}
int game::getLeft() {
    return LEFT;
}
int game::getUp() {
    return UP;
}
int game::getDown() {
    return DOWN;
}
int game::getEsc() {
    return ESC;
}
int game::getMenu() {
    return MENU;
}
//end of directio algos

/* ALGORITHM (crucial)
* This loads all of the data from the save file in order to continue from a saved point
* it begins by opening the data file
* it then checks if the file is empty or not. If it's empty, the algo ends without updating any game values
* If the file isn't empty, it goes through and updates each value saved
*/
void game::updateFromSave() {
        std::ifstream saveData;
        saveData.open("data.txt");
        if (!saveData.fail()) {
            std::string line = ""; //buffer
            std::getline(saveData, line); //gets the health
            if (!saveData.eof()) {
                op.setHealth(stoi(line));
                std::getline(saveData, line); //gets the name
                player_name = line;
                std::getline(saveData, line); //gets the progress
                progress = (stoi(line));
                //this stuff updates the map name to load a new map (possibly)
                name_of_map = "Level_";
                name_of_map += std::to_string(progress);
                name_of_map += ".txt";
                current_map.changeName(name_of_map); //this changes the map
                std::getline(saveData, line); //gets string of collectibles
                collectibles = line;
            }
            saveData.close();
        }
    return;
}
//This determines whether or not the player is about to enter a goal (unused)
bool game::goalFinder() {
    if (current_map.accessTile(op.getPlayerCoords().getX(),op.getPlayerCoords().getY()) == '@') { //Is the player on a goal tile?
        return true;
    }
    return false;
}
/* ALGORITHM (crucial)
* This updates the game for when the player enters a goal
* it starts by getting the progress, which acts as the current map number.
* if the progress is 6, then the game will end and the player will have won!
* If not, it updates the map and loads the new one to let the player continue
*/
void game::goal() {
    ++progress;
    if(progress == 6) { //did the player finish?
        system("cls");
        progress = 1;
        //sends the player back to level 1
        name_of_map = "Level_";
        name_of_map += std::to_string(progress);
        name_of_map += ".txt";
        op.setPlayerCoords(1,1);
        current_map.changeName(name_of_map);
        //prints out victory message!
        std::cout << "You have completed the game! Congrats :D! Press a key to be brought to the menu!";
        _getch();
        pause();
    }
    //changes the map to the next level
    name_of_map = "Level_";
    name_of_map += std::to_string(progress);
    name_of_map += ".txt";
    op.setPlayerCoords(1,1);
    current_map.changeName(name_of_map);
    system("cls");
    refresh();
    return;
}
//returns progress
std::string game::getProgress() {
    return std::to_string(progress);
}
//subtracts 2 from the health of the player
bool game::damage() {
    op.setHealth(op.getHealth() -2);
    if (op.getHealth() == 0) { //Did the player die?
        consoleAdd("You have died!");
        return true;
    }
    consoleAdd("-2 Health :("); //prints sad message
    return false;
}
//adds a collectible when the player clears a stage
void game::addCollectible(std::string coll) {
    collectibles = coll;
    return;
}
//returns all collectibles
std::string game::printCollectibles() {
    return collectibles;
}