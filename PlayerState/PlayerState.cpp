#include "PlayerState.hpp"
#include "../Player.hpp"
#include "../Game.hpp"

Button PlayerState::m_button {  {247/600.f,365/500.f,424/600.0f,445/500.f},{247/600.f,271/500.f,424/600.0f,350/500.f},{0.8f,-0.2f},{0.3f,0.2f}};

void PlayerState::exit_state(PlayerStateResult *result) const
{
    on_exit();
    m_p->set_state(m_previousState);
    if (m_thenFunc) m_thenFunc(m_p, result);

}

// TODO: default renders
void PlayerState::render_deck(VertexBatch* batch) const {
    m_p->getDeck().on_render(batch);
}
void PlayerState::render_hand(VertexBatch* batch) const {
    m_p->getHand().on_render(batch, false);
}
void PlayerState::render_played(VertexBatch* batch) const {
    m_p->getBoard().on_render(batch);
}
void PlayerState::render_piles(VertexBatch* batch) const {
    m_p->getGame()->render_piles(batch);
}
void PlayerState::render_discard(VertexBatch* batch) const {
    m_p->getDiscard().on_render(batch);
}
