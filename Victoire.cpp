#include "Victoire.hpp"

#include "Player.hpp"

Victoire::Victoire(int VictoryPoint, std::string name, int cost, glm::vec4 uvs) : Type(name, cost, uvs), VictoryPoint(VictoryPoint){}

Victoire::~Victoire(){
    std::cout << "Victoire destructor" << std::endl;
}
void Victoire::onTrash(Player* player) const {
    player->addVictoryPoints(-VictoryPoint);
}
void Victoire::onAddToDeck(Player* player) const {
    player->addVictoryPoints(VictoryPoint);
}
