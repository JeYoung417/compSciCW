
#include <iostream>
#include <memory>
#include <iterator>
#include <vector>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include <string.h>
#include "GameObject.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r5 = new Room(&r5name, &r5desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r1 = new Room(&r1name, &r1desc);
    auto * object1 = new GameObject(&object1Name, &object1Desc, &object1Key);
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    r1->setNorth(r2);
    r2->setSouth(r1);
    r2->setWest(r3);
    r3->setEast(r2);
    r3->setSouth(r4);
    r4->setNorth(r3);
    r4->setEast(r5);
    r5->setWest(r4);
    r1->addToRoom(object1);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */

        char commandChars[commandBuffer.length() + 1];
        strcpy(commandChars, commandBuffer.c_str());
        std::vector<std::string> command;
        auto stringToken = strtok(commandChars, " ");
        while(stringToken != NULL){
            command.push_back(stringToken);
            stringToken = strtok(NULL, " ");
        }

        if(command.size() > 2){
            wrapOut(&badCommand);
            wrapEndPara();
            continue;
        }
        else if(command.size() == 1) {
            if (command[0] == "north" || command[0] == "n") {
                commandOk = true;
                Room *northRoom = currentState->getCurrentRoom()->getNorth();
                if (northRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(northRoom);
                }
            }

            else if(command[0] == "south" || command[0] == "s") {
                commandOk = true;
                Room *southRoom = currentState->getCurrentRoom()->getSouth();
                if (southRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(southRoom);
                }
            }
            else if(command[0] == "east" || command[0] == "e") {
                commandOk = true;
                Room *eastRoom = currentState->getCurrentRoom()->getEast();
                if (eastRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(eastRoom);
                }
            }
            else if(command[0] == "west" || command[0] == "w") {
                commandOk = true;
                Room *westRoom = currentState->getCurrentRoom()->getWest();
                if (westRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(westRoom);
                }
            }


        }
        else if(command.size() == 2){
            if(command[0] == "get") {
                commandOk = true;
                GameObject *roomObject = currentState->getCurrentRoom()->getByKey(command[1]);
                if (roomObject != NULL) {
                    currentState->addToInv(roomObject);
                    currentState->getCurrentRoom()->removeFromRoom(roomObject);
                    currentState->getCurrentRoom()->describe();
                    wrapOut(roomObject->getObjectName());
                    wrapOut(&roomObjectAddedToInv);
                }
                else {
                    wrapOut(&badObject);
                }
                wrapEndPara();
            }

            else if(command[0] == "drop"){
                commandOk = true;
                GameObject *invObject = currentState->getByKey(command[1]);
                if (invObject != NULL) {
                    currentState->getCurrentRoom()->addToRoom(invObject);
                    currentState->removeFromInv(invObject);
                    currentState->getCurrentRoom()->describe();
                    wrapOut(invObject->getObjectName());
                    wrapOut(&invObjectAddedToRoom);
                }
                else {
                    wrapOut(&badObject);
                }
                wrapEndPara();
            }

           else if(command[0] == "examine") {
                commandOk = true;
                GameObject *roomObject = currentState->getCurrentRoom()->getByKey(command[1]);
                if (roomObject != NULL) {
                    currentState->getCurrentRoom()->describe();
                    wrapOut(roomObject->getObjectDescription());
                }
                else {
                    wrapOut(&badObject);
                }
                wrapEndPara();
            }
        }

        else {                    /* Bad command */
            wrapOut(&badCommand);
            wrapEndPara();
        }
        /* Quit command */
        if (command[0] == "quit") {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}