#include "GameObject.h"
#include <string>

GameObject::GameObject(const string *_name, const string *_desc, const string *_keyword) :
        name(_name), description(_desc), keyword(_keyword) {};

const string* GameObject::getObjectName(){
    return name;
}

const string* GameObject::getObjectDescription(){
    return description;
}

const string* GameObject::getObjectKeyword(){
    return keyword;
}
