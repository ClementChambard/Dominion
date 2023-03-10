#ifndef PLAYERSTATE_H_
#define PLAYERSTATE_H_

#include <functional>
#include "../VertexBatch.hpp"
#include "../Button.hpp"

struct PlayerStateResult {
        private:
    virtual void empty() {}
    // Make subclass for different states
};

class Player;

class PlayerState {
    public:
        PlayerState(Player* p, PlayerState* previousState) : m_p(p), m_previousState(previousState) {};
        virtual ~PlayerState() = default;

        PlayerState* then(std::function<void(Player*, PlayerStateResult*)> f) { m_thenFunc = f; return this; }

        virtual void on_entry() = 0;
        virtual void on_exit() const = 0;

        virtual void on_tick() = 0;
        virtual void on_render(VertexBatch* batch) = 0;
        virtual void on_renderUI(VertexBatch* batch) = 0;

        virtual void exit_state(PlayerStateResult* result) const;

    protected:
        Player* player() const { return m_p; }
        PlayerState* previousState() const { return m_previousState; }

        virtual void render_deck(VertexBatch* batch) const;
        virtual void render_hand(VertexBatch* batch) const;
        virtual void render_played(VertexBatch* batch) const;
        virtual void render_piles(VertexBatch* batch) const;
        virtual void render_discard(VertexBatch* batch) const;

        static Button m_button;

    private:
        Player* m_p;
        PlayerState* m_previousState;
        std::function<void(Player*, PlayerStateResult*)> m_thenFunc = nullptr;
};


#endif // PLAYERSTATE_H_
