#include "WorkShop.hpp"
#include "../Player.hpp"


WorkShop::WorkShop() : Type("WorkShop", 3, glm::vec4(2/7.0f, 0.8f, 3/7.0f, 1.0f), {CardType::ACTION}){}

void WorkShop::onPlay(Player* player) const {
    player->set_state(new PlayerStateBuyCards(player , player->get_state(),4,1));
}