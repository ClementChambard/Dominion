#include <iostream> 
#include <vector>

#ifndef CouncilRoom_H
#define CouncilRoom_H

#include "ActionSimple.hpp"

class CouncilRoom : public ActionSimple 
{

    
public:
    CouncilRoom();

    void onPlay(Player* player) const override ;
    

};

#endif // Action_H
