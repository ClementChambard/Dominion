#include "MoneyLender.hpp"
#include "../Player.hpp"
#include "../Card.hpp"
#include "../PlayerState/PlayerStateTrashCards.hpp"

MoneyLender::MoneyLender() : Type("MoneyLender", 4, glm::vec4(4/7.f, 0.8f, 5/7.0f, 1.0f), {CardType::ACTION}) {}

void MoneyLender::onPlay(Player* player) const
{
    player->set_state(new PlayerStateTrashCards(player, player->get_state(), 0, 1, CardType::TREASURE, 0, 0))->then(
        [](Player* p, PlayerStateResult* res) {
            auto cast_res = dynamic_cast<PlayerStateTrashCards::Result*>(res);
            if (cast_res->nb_card_trashed == 1) p->addCoins(3);
        }
    );
}
