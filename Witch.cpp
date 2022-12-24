#include "Witch.hpp"
#include "Player.hpp"
#include "Game.hpp"

Witch::Witch() : ActionSimple(0,0,0,2,"Witch", 5, glm::vec4(4/7.f, 0.4f, 5/7.0f, 0.6f), {CardType::ACTION, CardType::ATTACK}){}

void Witch::onPlay(Player* player) const {
    ActionSimple::onPlay(player);
    player->getGame()->Attack(player, [](Player* p){
        p->getGame()->DistributeCard(p, CardPileType::CURSE, PlayerCards::DISCARD);
    });
}

