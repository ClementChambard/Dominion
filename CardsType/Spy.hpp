#include <iostream> 
#include <vector>

#ifndef Spy_H
#define Spy_H

#include "ActionSimple.hpp"

class Spy : public ActionSimple 
{

public:
    Spy();
    void onPlay(Player* player) const override ;
};

#endif // Action_H
