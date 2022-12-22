#include <iostream> 
#include <vector>

#ifndef Mine_H
#define Mine_H

#include "Type.hpp"

class Mine : public Type 
{

    
public:
    Mine();
    ~Mine();
    void onPlay(Player* player) const override ;
    

};

#endif // Action_H