#include "Militia.hpp"
#include "../Player.hpp"
#include "../PlayerState/PlayerStateDiscardCards.hpp"
#include "../Game.hpp"

Militia::Militia() : ActionSimple(0,0,2,0,"Militia", 3, glm::vec4(3/7.f, 0.8f,4/7.0f, 1.0f), {CardType::ACTION, CardType::ATTACK})
{
}

void Militia::onPlay(Player* player) const 
{
    ActionSimple::onPlay(player);
    player->getGame()->Attack(player, [](Player* p){
        int nbToDiscard = p->getHand().size() - 3;
        if (nbToDiscard <= 0)
            return;
        
        p->set_state(new PlayerStateDiscardCards(p, p->get_state(), nbToDiscard, nbToDiscard));
       
    });
    
}