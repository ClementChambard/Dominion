#include "Remodel.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateTrashCards.hpp"

Remodel::Remodel() : Type("Remodel", 4, glm::vec4(0.f, 0.0f, 1/7.0f, 0.2f), {CardType::ACTION}){}

void Remodel::onPlay(Player* player) const 
{
    player->set_state(new PlayerStateTrashCards(player, player->get_state(), 0, 1))->then(
        [](Player* p, PlayerStateResult* res) {
            PlayerStateTrashCards::Result* cast_res = dynamic_cast<PlayerStateTrashCards::Result*>(res);
            if (cast_res->nb_card_trashed == 0) return;
            int cost = cast_res->types_trashed[0]->getCost() + 2;
            p->set_state(new PlayerStateBuyCards(p, p->get_state(), cost, 1));
        }
    );
}
