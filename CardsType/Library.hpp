#include <iostream> 
#include <vector>

#ifndef Library_H
#define Library_H

#include "Type.hpp"

class Library : public Type 
{

public:
    Library();

    void onPlay(Player* player) const override ;

};


#endif // Action_H
