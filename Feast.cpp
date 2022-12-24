#include "Feast.hpp"
#include "Player.hpp"
#include "Game.hpp"

Feast::Feast() : Type("Feast", 4, glm::vec4(5/7.f, 0.4f, 6/7.0f, 0.6f), {CardType::ACTION}){}

void Feast::onPlay(Player* player) const
{
    player->getBoard().remove(player->getBoard().size()-1);
    player->set_state(new PlayerStateBuyCards(player, player->get_state(), 5, 1));
}
