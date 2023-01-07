#ifndef PLAYERSTATEACTIONS_H_
#define PLAYERSTATEACTIONS_H_

#include "PlayerState.hpp"

class PlayerStateActions : public PlayerState {
    public:
        PlayerStateActions(Player* p, PlayerState* prevState) : PlayerState(p, prevState) { on_entry(); }

        void on_entry() override;
        void on_exit() const override;
        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;
};

#endif // PLAYERSTATEACTIONS_H_
