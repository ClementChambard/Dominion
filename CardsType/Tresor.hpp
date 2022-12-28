#include <iostream> 
#include <vector>

#ifndef Tresor_h
#define Tresor_h

#include "Type.hpp"

class Tresor : public Type 
{
private:
    int coin;

public:
    Tresor(int coin, std::string name, int cost, glm::vec4 uvs);

    void onDiscard(Player* player) const override ;
    void onDraw(Player* player) const override ;
    void onTrash(Player* player)const override;
};


#endif // Action_H
