#include <iostream> 
#include <vector>

#ifndef Remodel_H
#define Remodel_H

#include "Type.hpp"

class Remodel : public Type 
{

    
public:
    Remodel();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
