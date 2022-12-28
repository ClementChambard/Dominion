#include <iostream> 
#include <vector>

#ifndef Adventurer_H
#define Adventurer_H

#include "Type.hpp"

class Adventurer : public Type 
{

    
public:
    Adventurer();
    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
