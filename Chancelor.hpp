#include <iostream> 
#include <vector>

#ifndef Chancelor_H
#define Chancelor_H

#include "ActionSimple.hpp"

class Chancelor : public ActionSimple 
{

    
public:
    Chancelor();
    ~Chancelor();
    void onPlay(Player* player) const override ;
    

};

#endif // Action_H