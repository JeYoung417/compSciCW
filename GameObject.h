#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#include <string>
#include <forward_list>
#include <list>

using std::string;


class GameObject {

        const string* name;

        const string* description;

        const string* keyword;

public:

    GameObject(const string *_name, const string *_desc, const string *_keyword);

    const string* getObjectName();
    const string* getObjectDescription();
    const string* getObjectKeyword();

};

#endif //TEXTADV_GAMEOBJECT_H
