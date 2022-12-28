#include <iostream> 
#include <vector>

#ifndef Feast_H
#define Feast_H

#include "Type.hpp"

class Feast : public Type 
{

    
public:
    Feast();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
