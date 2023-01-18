#ifndef PlayerStateBool_H_
#define PlayerStateBool_H_

#include "PlayerState.hpp"

class PlayerStateBool : public PlayerState {
    
    public:
        PlayerStateBool(Player* p, PlayerState* prevState,std::string q) : PlayerState(p, prevState), m_question(q) { on_entry(); }

        void on_entry() override {}
        void on_exit() const override {}
        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;


        struct Result : PlayerStateResult {
            bool res;
            Result(bool b) : res(b) {}
        };

    private:
        std::string m_question;
    static Button no;
    static Button yes;
};

#endif // PlayerStateBool_H_
