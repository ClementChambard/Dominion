#include "CardPile.hpp"
#include "Mouse.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <algorithm>
#include "SpriteFont.hpp"

#define CARD_PILE_HEIGHT_INCREASE 0.01f
#define CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MIN 10
#define CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MAX 60
#define CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MUL 0.0005f

float getHInc(int /* size */) {
    //float s_in = glm::clamp(size, CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MIN, CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MAX) - CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MIN;
    return CARD_PILE_HEIGHT_INCREASE;// - s_in * CARD_PILE_HEIGHT_INCREASE_SCALE_FACTOR_MUL;
}

void CardPile::on_tick() {
    if (m_targetPos != m_pos) {
        glm::vec3 dst = m_targetPos - m_pos;
        if (dst.x*dst.x+dst.y*dst.y+dst.z*dst.z < CARD_SNAP_DISTANCE_SQ_TRESHOLD) m_pos = m_targetPos;
        else m_pos += dst/CARD_MOVEMENT_PROPORTION;
    }
    m_inAnim = false;
    for (Card* c : m_data) m_inAnim = m_inAnim || c->isInAnim();
    float h = 0.f;
    float hInc = getHInc(m_data.size());
    for (Card* c : m_data) {
        c->moveTo(m_pos+glm::vec3(0.f,0.f,h));
        if (m_faceUp) c->rotateYTo(0.f);
        else          c->rotateYTo(glm::pi<float>());
        c->rotateZTo(0.f);
        c->on_tick();
        h += hInc;
    }
    if (isHovered() && !m_lowlighted && m_data.size() > 0) m_data.back()->set_hovered(true);
    else if (m_data.size() > 0) m_data.back()->set_hovered(false);
}

void CardPile::on_render(VertexBatch* batch, bool h) {
    for (size_t i = 0; i < m_data.size(); i++) {
        Card* c = m_data[i];
        if ((h && !isHovered()) || !h || m_lowlighted || i != m_data.size()-1) c->on_render(batch, h && !m_lowlighted && isHovered() && (i == m_data.size() - 1), m_lowlighted);
    }
    if (isHovered()) SpriteFont::last_created_instance->renderText(std::to_string(m_data.size()), Mouse::getposNormalized()+glm::vec2{0.05f, -0.05f}, {0.5f, 0.5f}, {0,255,0,255});
}

bool CardPile::isHovered() const {
    if (m_data.size() == 0) return false;
    float h = m_pos.z + getHInc(m_data.size()) * m_data.size();
    glm::vec2 mpos = Mouse::toWorldCurrent(h);
    glm::vec2 s = m_data.back()->getSize();
    return mpos.x > m_pos.x - s.x/2 && mpos.x < m_pos.x + s.x/2 && mpos.y > m_pos.y - s.y/2 && mpos.y < m_pos.y + s.y/2;
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
    float hInc = getHInc(m_data.size());
    m_pos = m_targetPos;
    for (Card* c : m_data) {
        c->set_pos(m_pos+glm::vec3(0.f,0.f,h));
        if (m_faceUp) c->set_rotY(0.f);
        else          c->set_rotY(glm::pi<float>());
        c->set_rotZ(0.f);
        h += hInc;
    }
}

void CardPile::shuffle() {
    static std::random_device rd;
    static auto rng = std::default_random_engine { rd() };
    std::shuffle(m_data.begin(), m_data.end(), rng);
}
