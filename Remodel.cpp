#include "Remodel.hpp"
#include "Player.hpp"
#include "Game.hpp"

Remodel::Remodel() : Type("Remodel", 4, glm::vec4(0.f, 0.0f, 1/7.0f, 0.2f), {CardType::ACTION}){}

Remodel::~Remodel(){
    std::cout << "Remodel destructor" << std::endl;
}

void Remodel::onPlay(Player* player) const 
{
    player->allowUpgradeCard(2,0);
  
   
}
