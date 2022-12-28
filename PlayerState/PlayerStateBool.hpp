#ifndef PlayerStateBool_H_
#define PlayerStateBool_H_

#include "PlayerState.hpp"

class PlayerStateBool : public PlayerState {
    
    public:
        PlayerStateBool(Player* p, PlayerState* prevState,std::string) : PlayerState(p, prevState) {}

        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;


        struct Result : PlayerStateResult {
            bool res;
        };
};

#endif // PlayerStateBool_H_