#include <iostream> 
#include <vector>

#ifndef Cellar_H
#define Cellar_H

#include "ActionSimple.hpp"

class Cellar : public ActionSimple 
{

    
public:
    Cellar();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
