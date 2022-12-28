#include <iostream> 
#include <vector>

#ifndef WorkShop_H
#define WorkShop_H

#include "Type.hpp"

class WorkShop : public Type 
{

public:
    WorkShop();
    void onPlay(Player* player) const override ;
};

#endif // Action_H
