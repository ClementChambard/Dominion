#ifndef PLAYERSTATEBUYCARDS_H_
#define PLAYERSTATEBUYCARDS_H_

#include "PlayerState.hpp"
#include "VertexBatch.hpp"

class PlayerStateBuyCards : public PlayerState {
    public:
        PlayerStateBuyCards(Player* p, PlayerState* previousState, int money, int buys) :
            PlayerState(p, previousState), m_money(money), m_buys(buys) {}

        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;

    private:
        int m_money;
        int m_buys;
};

#endif // PLAYERSTATEBUYCARDS_H_
