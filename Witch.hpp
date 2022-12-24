#include <iostream> 
#include <vector>

#ifndef Witch_H
#define Witch_H

#include "ActionSimple.hpp"

class Witch : public ActionSimple 
{

public:
    Witch();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
