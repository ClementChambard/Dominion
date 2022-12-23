#include "PlayerState.hpp"
#include "Player.hpp"

void PlayerState::exit_state(PlayerStateResult *result) const
{
    if (m_thenFunc) m_thenFunc(m_p, result);
    m_p->set_state(m_previousState);
}
