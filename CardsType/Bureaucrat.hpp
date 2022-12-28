#include <iostream> 
#include <vector>

#ifndef Bureaucrat_H
#define Bureaucrat_H

#include "Type.hpp"

class Bureaucrat : public Type 
{

public:
    Bureaucrat();
    void onPlay(Player* player) const override ;
};

#endif // Action_H
