#include "Spy.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateBool.hpp"

Spy::Spy() : ActionSimple(1,0,0,1,"Spy", 4, glm::vec4(5/7.f, 0.6f, 6/7.0f, 0.8f), {CardType::ACTION, CardType::ATTACK}){}

void Spy::onPlay(Player* player) const {
    ActionSimple::onPlay(player);
    auto action  = [](Player*player){
        CardPile deck = player->getDeck();
        if (!deck.getOnTop()) {
            deck.transmitFrom(player->getDiscard());
            deck.shuffle();
        }
        Card* newCard = deck.getOnTop();
        deck.removeOnTop();
        player->set_state(new PlayerStateBool(player, nullptr, "Do you want to keep the card " + newCard->getType()->getName() + "?"))
            ->then([player, newCard](Player* p, PlayerStateResult* result) {
                PlayerStateBool::Result* cast_res = dynamic_cast<PlayerStateBool::Result*>(result);
                if (cast_res->res) {
                    p->getHand().Add(newCard);
                } else {
                    p->getDiscard().AddOnTop(newCard);
                }
            });
    };
    action(player);
    player->getGame()->Attack(player, action);
}

