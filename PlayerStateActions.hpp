#ifndef PLAYERSTATEACTIONS_H_
#define PLAYERSTATEACTIONS_H_

#include "PlayerState.hpp"
#include "VertexBatch.hpp"

class PlayerStateActions : public PlayerState {
    public:
        PlayerStateActions(Player* p, PlayerState* prevState) : PlayerState(p, prevState) {}

        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;
};

#endif // PLAYERSTATEACTIONS_H_
