#include "Feast.hpp"
#include "Player.hpp"
#include "Game.hpp"

Feast::Feast() : Type("Feast", 4, glm::vec4(5/7.f, 0.4f, 6/7.0f, 0.6f)){}

Feast::~Feast(){
    std::cout << "Feast destructor" << std::endl;
}

void Feast::onPlay(Player* player) const 
{
    player->trashCard(player->getLastPlayedCard());
    player->allowbuyCard(5);


}