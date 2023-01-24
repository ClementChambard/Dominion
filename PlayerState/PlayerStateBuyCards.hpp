#ifndef PLAYERSTATEBUYCARDS_H_
#define PLAYERSTATEBUYCARDS_H_

#include "PlayerState.hpp"
#include "../CardsType/Type.hpp"

class PlayerStateBuyCards : public PlayerState {
    public:
        PlayerStateBuyCards(Player* p, PlayerState* previousState, int money, int buys, Type::CardType typeRestriction = Type::CardType::NONE, bool updatePlayerMoney = false ,bool directhand = false) :
            PlayerState(p, previousState), m_money(money), m_buys(buys), m_typeRestriction(typeRestriction), m_updatePlayerMoney(updatePlayerMoney),directhand(directhand)  { on_entry(); }

        void on_entry() override;
        void on_exit() const override;
        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;

    private:
        int m_money;
        int m_buys;
        Type::CardType m_typeRestriction;
        bool m_updatePlayerMoney;
        bool directhand ;
};

#endif // PLAYERSTATEBUYCARDS_H_
