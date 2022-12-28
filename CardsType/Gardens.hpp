#include <iostream> 
#include <vector>

#ifndef Gardens_H
#define Gardens_H

#include "Type.hpp"

class Gardens : public Type 
{

public:
    Gardens();

    void onTrash(Player* player) const override ;
    void onAddToDeck(Player* player) const override ;
    void onDeckChange(Player* player, int oldCardNumber, int newCardNumber) const override ;

};


#endif // Action_H
