#include "CardBoard.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Mouse.hpp"

#define CARD_BOARD_SIZE_MAX 5.f
#define CARD_BOARD_SPACE_MAX 0.9f

void CardBoard::on_tick()
{
    if (m_targetPos != m_pos) {
        glm::vec3 dst = m_targetPos - m_pos;
        if (dst.x*dst.x+dst.y*dst.y+dst.z*dst.z < CARD_SNAP_DISTANCE_SQ_TRESHOLD) m_pos = m_targetPos;
        else m_pos += dst/CARD_MOVEMENT_PROPORTION;
    }
    float space_between = CARD_BOARD_SPACE_MAX;
    if ((space_between*m_data.size()) > CARD_BOARD_SIZE_MAX) space_between = CARD_BOARD_SIZE_MAX / m_data.size();
    float x = m_pos.x - (space_between*(m_data.size() - 1)) / 2.f;
    for (size_t i = 0; i < m_data.size(); i++) {
        m_data[i]->moveTo({x, m_pos.y, m_pos.z});
        m_data[i]->rotateYTo(0);
        m_data[i]->rotateZTo(0);
        x += space_between;
        m_data[i]->on_tick();
    }
}

void CardBoard::fixPos()
{
    m_pos = m_targetPos;
    float space_between = CARD_BOARD_SPACE_MAX;
    if ((space_between*m_data.size()) > CARD_BOARD_SIZE_MAX) space_between = CARD_BOARD_SIZE_MAX / m_data.size();
    float x = m_pos.x - (space_between*(m_data.size() - 1)) / 2.f;
    for (size_t i = 0; i < m_data.size(); i++) {
        m_data[i]->set_pos({x, m_pos.y, m_pos.z});
        m_data[i]->set_rotY(0);
        m_data[i]->set_rotZ(0);
        x += space_between;
    }
}

void CardBoard::on_render(VertexBatch* batch)
{
    for (size_t i = 0; i < m_data.size(); i++)
        m_data[i]->on_render(batch);
}
