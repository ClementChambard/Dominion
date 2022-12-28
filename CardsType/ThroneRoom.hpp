#include <iostream> 
#include <vector>

#ifndef ThroneRoom_H
#define ThroneRoom_H

#include "Type.hpp"

class ThroneRoom : public Type 
{
public:
    ThroneRoom();
    void onPlay(Player* player) const override ;

};


#endif // Action_H
