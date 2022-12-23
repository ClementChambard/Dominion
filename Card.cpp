#include "Card.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Card::on_tick() {
    m_inAnim = false;
    if (m_targetPosition != m_position) {
        glm::vec3 dst = m_targetPosition - m_position;
        if (dst.x*dst.x+dst.y*dst.y+dst.z*dst.z < CARD_SNAP_DISTANCE_SQ_TRESHOLD) m_position = m_targetPosition;
        else m_position += dst/CARD_MOVEMENT_PROPORTION;
        m_inAnim = true;
    }
    if (m_targetRotY != m_rotY) {
        float dst = m_targetRotY - m_rotY;
        if (fabs(dst) < CARD_SNAP_ANGLE_TRESHOLD) m_rotY = m_targetRotY;
        else m_rotY += dst/CARD_MOVEMENT_PROPORTION;
        m_recalculateRot = true;
        m_inAnim = true;
    }
    if (m_targetRotZ != m_rotZ) {
        float dst = m_targetRotZ - m_rotZ;
        if (fabs(dst) < CARD_SNAP_ANGLE_TRESHOLD) m_rotZ = m_targetRotZ;
        else m_rotZ += dst/CARD_MOVEMENT_PROPORTION;
        m_recalculateRot = true;
        m_inAnim = true;
    }
    if (m_recalculateRot) {
        m_rotationMatrix = glm::rotate(glm::rotate(glm::mat4(1.0f), m_rotY, glm::vec3(0,1,0)), m_rotZ, glm::vec3(0,0,1));
    }
    m_recalculateRot = false;

    if (!m_hovered) m_hoveredAnimTime = 0.f;
    else m_hoveredAnimTime += 0.1f;
}

void Card::on_render(VertexBatch* batch, bool hovered) {
    glm::vec3 pos = m_position;
    glm::mat4 rot = m_rotationMatrix;
    if (hovered) {
        if (m_hoveredAnimTime < 1.f) pos += glm::vec3(0.f,0.2f,1.f) * m_hoveredAnimTime;
        else pos += glm::vec3(0.f,0.2f,1.f);
        rot = glm::rotate(rot, sinf(m_hoveredAnimTime/2.f)/10.f, glm::vec3{0,0,1});
    }
    batch->draw_rectangle(pos.x, pos.y, pos.z, 0.8f, 1.f, rot, m_type->getUvs());
    batch->draw_rectangle(pos.x, pos.y, pos.z, -0.8f, 1.f, rot, {6/7.f,0.8f,1.f,1.f});
}
