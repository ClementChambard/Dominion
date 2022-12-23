#include "Mine.hpp"
#include "Player.hpp"
#include "Game.hpp"

Mine::Mine() : Type("Mine", 5, glm::vec4(0.f, 0.6f, 1/7.0f, 0.8f), {CardType::ACTION}){}

Mine::~Mine(){
    std::cout << "Mine destructor" << std::endl;
}

void Mine::onPlay(Player* player) const 
{
    player->allowUpgradeCard(3,1); // mine can upgrade only tresure cards
}
