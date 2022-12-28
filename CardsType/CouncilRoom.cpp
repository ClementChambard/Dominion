#include "CouncilRoom.hpp"
#include "../Player.hpp"
#include "../Game.hpp"

CouncilRoom::CouncilRoom() : ActionSimple(0,1,0,4,"CouncilRoom", 5, glm::vec4(1/7.f, 0.2f, 2/7.0f, 0.4f)){}

void CouncilRoom::onPlay(Player* player) const
{
    ActionSimple::onPlay(player);
    player->getGame()->Attack(player, [](Player* p){
        p->draw(1);
    },false);
}
