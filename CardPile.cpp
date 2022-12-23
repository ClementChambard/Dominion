#include "CardPile.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <algorithm>

#define CARD_PILE_HEIGHT_INCREASE 0.02f

void CardPile::on_tick() {
    if (m_targetPos != m_pos) {
        glm::vec3 dst = m_targetPos - m_pos;
        if (dst.x*dst.x+dst.y*dst.y+dst.z*dst.z < CARD_SNAP_DISTANCE_SQ_TRESHOLD) m_pos = m_targetPos;
        else m_pos += dst/CARD_MOVEMENT_PROPORTION;
    }
    m_inAnim = false;
    for (Card* c : m_data) m_inAnim = m_inAnim || c->isInAnim();
    float h = 0.f;
    for (Card* c : m_data) {
        c->moveTo(m_pos+glm::vec3(0.f,0.f,h));
        if (m_faceUp) c->rotateYTo(0.f);
        else          c->rotateYTo(glm::pi<float>());
        c->rotateZTo(0.f);
        c->on_tick();
        h += CARD_PILE_HEIGHT_INCREASE;
    }
}

void CardPile::on_render(VertexBatch* batch) {
    for (Card* c : m_data) {
        c->on_render(batch);
    }
}

void CardPile::transmitFrom(CardPile& cp) {
    while (!cp.m_data.empty()) {
        m_data.push_back(cp.m_data.back());
        cp.m_data.pop_back();
        m_inAnim = true;
        cp.m_inAnim = true;
    }
}

void CardPile::fixPos() {
    float h = 0.f;
    m_pos = m_targetPos;
    for (Card* c : m_data) {
        c->set_pos(m_pos+glm::vec3(0.f,0.f,h));
        if (m_faceUp) c->set_rotY(0.f);
        else          c->set_rotY(glm::pi<float>());
        c->set_rotZ(0.f);
        h += CARD_PILE_HEIGHT_INCREASE;
    }
}

void CardPile::shuffle() {
    static std::random_device rd;
    static auto rng = std::default_random_engine { rd() };
    std::shuffle(m_data.begin(), m_data.end(), rng);
    for (Card* c : m_data) {
        c->moveTo(m_pos+glm::vec3((rand()%100)/50.f-1.f,(rand()%100)/50.f-1.f,CARD_PILE_HEIGHT_INCREASE*m_data.size()/2.f));
    }
}