#include "PlayerStateDiscardCards.hpp"
#include "../Player.hpp"
#include "../Mouse.hpp"

void PlayerStateDiscardCards::on_entry() {
    m_prevRestriction = player()->getHand().getHighlight();
    player()->getHand().highlightCard(m_typeRestriction);
}

void PlayerStateDiscardCards::on_exit() const {
    player()->getHand().highlightCard(m_prevRestriction);
}

void PlayerStateDiscardCards::on_tick() {
    // check nb of discard left
    if (m_res.nb_card_discarded == m_discardsMax) { exit_state(&m_res); return; }
    
    // check if player has discardable cards in hand
    //bool hasAction = false;
    //for (auto c : player()->getHand()) if (c->getType()->isType(Type::CardType::ACTION)) hasAction = true;
    //if (!hasAction) { exit_state(nullptr); return; }

    // check click on card in hand
    int hoveredCard = player()->getHand().getHoveredId();
    if (hoveredCard >= 0) {
        Card* c = player()->getHand().get(hoveredCard);
        if (Mouse::press() && c->getType()->isType(m_typeRestriction))
        {
            player()->getHand().remove(hoveredCard);
            player()->getDiscard().AddOnTop(c);
            c->getType()->onDiscard(player());
            m_res.nb_card_discarded++;
            m_res.types_discarded.push_back(c->getType());
        }
    }

    if (m_button.isHovered() && Mouse::press() && m_res.nb_card_discarded > m_discardsMin) { exit_state(&m_res); return; }
}

void PlayerStateDiscardCards::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_played(batch);
    render_piles(batch);
    player()->getHand().on_render(batch, true);
}

void PlayerStateDiscardCards::on_renderUI(VertexBatch* batch) {
    PlayerState::m_button.onUpdate(batch);
}
