#ifndef COMPONNENT_H
#define COMPONNENT_H

#include <iostream>

class Component{
public:
    unsigned int id;

    std::string name;

    Component(){};
    virtual ~Component(){};
};

#endif // COMPONNENT_H
