//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"

class State {
    Room *currentRoom;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;
    std::list<GameObject*> inventory;
    GameObject* getByKey(const string& Key);
    void addToInv(GameObject* roomObject);
    void removeFromInv(GameObject* invObject);

};


#endif //TEXTADV_STATE_H
