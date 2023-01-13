#include "Cellar.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateDiscardCards.hpp"

Cellar::Cellar() : ActionSimple(1,0,0,0,"Cellar", 2, glm::vec4(0.f, 0.8f, 1/7.0f, 1.0f)){}

void Cellar::onPlay(Player* player) const 
{
    ActionSimple::onPlay(player);
        player->set_state(new PlayerStateDiscardCards(player, player->get_state(), 0, player->getHand().size()))
        ->then([] (Player* p , PlayerStateResult* res){
            PlayerStateDiscardCards::Result* cast_res = dynamic_cast<PlayerStateDiscardCards::Result*>(res);
            p->draw(cast_res->nb_card_discarded);
        });
}
