#include <iostream> 
#include <vector>

#ifndef Victoire_H
#define Victoire_H

#include "Type.hpp"

class Victoire : public Type 
{
private:
    int VictoryPoint;
public:
    Victoire(int Victoire, std::string name, int cost, glm::vec4 uvs);
    ~Victoire();
    void onTrash(Player* player) const override ;
    void onAddToDeck(Player* player) const override ;

};


#endif // Action_H
