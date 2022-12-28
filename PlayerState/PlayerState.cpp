#include "PlayerState.hpp"
#include "../Player.hpp"

void PlayerState::exit_state(PlayerStateResult *result) const
{
    on_exit();
    if (m_thenFunc) m_thenFunc(m_p, result);
    m_p->set_state(m_previousState);
}

// TODO: default renders
void PlayerState::render_deck(VertexBatch*) const {}
void PlayerState::render_hand(VertexBatch*) const {}
void PlayerState::render_played(VertexBatch*) const {}
void PlayerState::render_piles(VertexBatch*) const {}
void PlayerState::render_discard(VertexBatch*) const {}
