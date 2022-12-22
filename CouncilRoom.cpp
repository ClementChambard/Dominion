#include "CouncilRoom.hpp"

#include "Player.hpp"

#include "Game.hpp"

CouncilRoom::CouncilRoom() : ActionSimple(0,1,0,4,"CouncilRoom", 5, glm::vec4(1/7.f, 0.2f, 2/7.0f, 0.4f)){}

CouncilRoom::~CouncilRoom(){
    std::cout << "CouncilRoom destructor" << std::endl;
}

void CouncilRoom::onPlay(Player* player) const
{
    player->draw(4);
    
    for ( Player& p : player->getGame()->getPlayers())
    {
        if (&p != player)
        {
            p.draw(1);
        }
    }
}