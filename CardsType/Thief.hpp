#include <iostream> 
#include <vector>

#ifndef Thief_H
#define Thief_H

#include "Type.hpp"

class Thief : public Type 
{

public:
    Thief();
    void onPlay(Player* player) const override ;
};

#endif // Action_H
