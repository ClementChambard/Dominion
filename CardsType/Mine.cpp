#include "Mine.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateTrashCards.hpp"


Mine::Mine() : Type("Mine", 5, glm::vec4(0.f, 0.6f, 1/7.0f, 0.8f), {CardType::ACTION}){}

void Mine::onPlay(Player* player) const
{
    player->set_state(new PlayerStateTrashCards(player, player->get_state(), 0, 1, CardType::TREASURE))->then(
        [](Player* p, PlayerStateResult* res) {
            PlayerStateTrashCards::Result* cast_res = dynamic_cast<PlayerStateTrashCards::Result*>(res);
            if (cast_res->nb_card_trashed == 0) return;
            int cost = cast_res->types_trashed[0]->getCost() + 3;
            p->set_state(new PlayerStateBuyCards(p, p->get_state(), cost, 1, CardType::TREASURE));
        }
    );
}
