#include <iostream> 
#include <vector>

#ifndef Militia_H
#define Militia_H

#include "ActionSimple.hpp"

class Militia : public ActionSimple 
{

public:
    Militia();

    void onPlay(Player* player) const override ;

};


#endif // Action_H
