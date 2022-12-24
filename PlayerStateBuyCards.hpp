#ifndef PLAYERSTATEBUYCARDS_H_
#define PLAYERSTATEBUYCARDS_H_

#include "PlayerState.hpp"
#include "VertexBatch.hpp"
#include "Type.hpp"

class PlayerStateBuyCards : public PlayerState {
    public:
        PlayerStateBuyCards(Player* p, PlayerState* previousState, int money, int buys, Type::CardType typeRestriction = Type::CardType::NONE) :
            PlayerState(p, previousState), m_money(money), m_buys(buys), m_typeRestriction(typeRestriction) {}

        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;

    private:
        int m_money;
        int m_buys;
        Type::CardType m_typeRestriction;
};

#endif // PLAYERSTATEBUYCARDS_H_
