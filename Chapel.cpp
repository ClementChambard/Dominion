#include "Chapel.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "PlayerStateTrashCards.hpp"

Chapel::Chapel() : Type("Chapel", 2, glm::vec4(5/7.f, 0.0f, 6/7.0f, 0.2f), {CardType::ACTION}){}

void Chapel::onPlay(Player* player) const
{
    player->set_state(new PlayerStateTrashCards(player, player->get_state(), 0, 4));
}
