#include "ThroneRoom.hpp"

#include "../Game.hpp"

ThroneRoom::ThroneRoom() : Type("Throne Room", 4, glm::vec4(0.f, 0.2f, 1/7.0f, 0.4f), {CardType::ACTION}){}

void ThroneRoom::onPlay(Player* player) const {
    player->addActions(1);
    player->setActionMultiplier(2);
}