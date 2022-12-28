#include <iostream> 
#include <vector>

#ifndef Moat_H
#define Moat_H

#include "ActionSimple.hpp"

class Moat : public ActionSimple 
{

public:
    Moat();
    bool onReact(Player* player) const override ;


    

};

#endif // Action_H
