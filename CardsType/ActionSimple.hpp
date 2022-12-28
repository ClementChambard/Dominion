#include <iostream> 
#include <vector>

#ifndef Action_H
#define Action_H

#include "Type.hpp"

class ActionSimple : public Type 
{
private:
    int action;
    int buy;
    int coin;
    int card;
public:
    ActionSimple(int action, int buy, int coin, int card, std::string name, int cost, glm::vec4 uvs, std::vector<CardType> const& types = {CardType::ACTION});

    void onPlay(Player* player) const override ;
    int getCoin() const {return coin;}

};


#endif // Action_H
