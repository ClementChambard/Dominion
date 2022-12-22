#include "Chapel.hpp"
#include "Player.hpp"
#include "Game.hpp"

Chapel::Chapel() : Type("Chapel", 2, glm::vec4(5/7.f, 0.0f, 6/7.0f, 0.2f)){}

Chapel::~Chapel(){
    std::cout << "Chapel destructor" << std::endl;
}

void Chapel::onPlay(Player* player) const 
{
    player->allowTrashCard(4);
}
