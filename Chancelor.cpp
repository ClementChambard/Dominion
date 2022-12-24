#include "Chancelor.hpp"
#include "Player.hpp"



Chancelor::Chancelor() : ActionSimple(0,0,2,0,"Chancelor", 3, glm::vec4(5/7.f, 0.2f, 6/7.0f, 0.4f)){}

void Chancelor::onPlay(Player* player) const
{
    ActionSimple::onPlay(player);
    player->getDeck().transmitTo(player->getDiscard());
}
