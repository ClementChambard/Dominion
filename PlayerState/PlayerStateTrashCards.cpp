#include "PlayerStateTrashCards.hpp"
#include "../Player.hpp"
#include "../Mouse.hpp"
#include "../SpriteFont.hpp"

void PlayerStateTrashCards::on_entry() {
    m_prevRestriction = player()->getHand().getHighlight();
    player()->getHand().highlightCard(m_typeRestriction);
}

void PlayerStateTrashCards::on_exit() const {
    player()->getHand().highlightCard(m_prevRestriction);
}

void PlayerStateTrashCards::on_tick() {
    // check nb of trash left
    if (m_res.nb_card_trashed == m_trashsMax) { exit_state(&m_res); return; }

    // check if player has trashable cards in hand
    //bool hasAction = false;
    //for (auto c : player()->getHand()) if (c->getType()->isType(Type::CardType::ACTION)) hasAction = true;
    //if (!hasAction) { exit_state(nullptr); return; }

    // check click on card in hand
    int hoveredCard = player()->getHand().getHoveredId();
    if (hoveredCard >= 0) {
        Card* c = player()->getHand().get(hoveredCard);
        if (Mouse::press() && c->getType()->isType(m_typeRestriction) && c->getType()->getCost() <= m_costMax && c->getType()->getCost() >= m_costMin)
        {
            player()->getHand().remove(hoveredCard);
            c->getType()->onTrash(player());
            m_res.nb_card_trashed++;
            m_res.types_trashed.push_back(c->getType());
        }
    }

    // check press on end discards button
    // then
    // exit_state() -> return is types of card trashed & nb trashed
    if (m_button.isHovered() && Mouse::press() && m_res.nb_card_trashed >= m_trashsMin) { exit_state(&m_res); return; }
}

void PlayerStateTrashCards::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_played(batch);
    render_piles(batch);
    player()->getHand().on_render(batch, true);
}

void PlayerStateTrashCards::on_renderUI(VertexBatch* batch) {
    PlayerState::m_button.onUpdate(batch);
    int darkness = (m_res.nb_card_trashed >= m_trashsMin) ? 255 : 128;
    SpriteFont::last_created_instance->renderText("End trashs", m_button.getPos()+glm::vec2{0.015,0}, {0.5f, 0.6f}, {darkness, darkness, darkness, 255});
}
