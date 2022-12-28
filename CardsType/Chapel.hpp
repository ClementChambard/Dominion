#include <iostream> 
#include <vector>

#ifndef Chapel_H
#define Chapel_H

#include "Type.hpp"

class Chapel : public Type 
{

    
public:
    Chapel();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
