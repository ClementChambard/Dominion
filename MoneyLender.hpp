#include <iostream> 
#include <vector>

#ifndef MoneyLender_H
#define MoneyLender_H

#include "Type.hpp"

class MoneyLender : public Type 
{

    
public:
    MoneyLender();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
