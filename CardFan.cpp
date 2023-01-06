#include "CardFan.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Mouse.hpp"

#define CARD_FAN_ANGLE_TOTAL_MAX 1.5f
#define CARD_FAN_ANGLE_BETWEEN_MAX 0.3f
#define CARD_FAN_CENTER_DIST 2.f
#define CARD_FAN_CENTER_X 0
#define CARD_FAN_CENTER_Y -1.2f

float angleFromPoint(float x, float y) {

    if (x == 0) return glm::pi<float>()/2.f;
    else if (x > 0) return glm::atan(y/x);
    else return glm::pi<float>() - glm::atan(-y/x);
}

void CardFan::on_tick()
{
    if (m_targetPos != m_pos) {
        glm::vec3 dst = m_targetPos - m_pos;
        if (dst.x*dst.x+dst.y*dst.y+dst.z*dst.z < CARD_SNAP_DISTANCE_SQ_TRESHOLD) m_pos = m_targetPos;
        else m_pos += dst/CARD_MOVEMENT_PROPORTION;
    }
    int nb_card = m_data.size();
    float ang_between = CARD_FAN_ANGLE_BETWEEN_MAX;
    if ((nb_card-1) * ang_between > CARD_FAN_ANGLE_TOTAL_MAX) ang_between = CARD_FAN_ANGLE_TOTAL_MAX / (nb_card-1);
    float ang_fst = (ang_between * (nb_card-1))/2.f;
    m_inAnim = false;

   
    glm::vec3 mousePosInFan = Mouse::toWorldCurrent(m_pos.z, {0.f, -1.f, 5.f}) - (m_pos+glm::vec3(CARD_FAN_CENTER_X,CARD_FAN_CENTER_Y,0.f));
    bool mouseInRange = (mousePosInFan.x*mousePosInFan.x+mousePosInFan.y*mousePosInFan.y) < (CARD_FAN_CENTER_DIST + 0.5f)*(CARD_FAN_CENTER_DIST + 0.5f);
    float mouseAngle = angleFromPoint(mousePosInFan.x, mousePosInFan.y) - glm::pi<float>()/2.f;
    m_hovered = -1;
    for (int i = m_data.size()-1; i >= 0; i--)
    {
        glm::vec3 pos = m_pos +
                        glm::vec3(CARD_FAN_CENTER_X, CARD_FAN_CENTER_Y, 0.f) +
                        glm::vec3(CARD_FAN_CENTER_DIST*cos(ang_fst+glm::pi<float>()/2.f),CARD_FAN_CENTER_DIST*sin(ang_fst+glm::pi<float>()/2.f),0.f);
        m_data[i]->moveTo(pos);
        m_data[i]->rotateYTo(0.f);
        m_data[i]->rotateZTo(ang_fst);
        m_inAnim = m_inAnim || m_data[i]->isInAnim();
        if (mouseInRange && mouseAngle > ang_fst - ang_between/2.f && mouseAngle < ang_fst + ang_between/2.f) {
            m_data[i]->set_hovered(true);
            m_hovered = i;
        } else m_data[i]->set_hovered(false);
        ang_fst -= ang_between;
        m_data[i]->on_tick();
    }
}

void CardFan::fixPos()
{
    m_pos = m_targetPos;
    int nb_card = m_data.size();
    float ang_between = CARD_FAN_ANGLE_BETWEEN_MAX;
    if ((nb_card-1.f) * ang_between > CARD_FAN_ANGLE_TOTAL_MAX) ang_between = CARD_FAN_ANGLE_TOTAL_MAX / (nb_card-1.f);
    float ang_fst = (ang_between * (nb_card-1.f))/2.f;
    for (int i = m_data.size()-1; i >= 0; i--)
    {
        glm::vec3 pos = m_pos +
                        glm::vec3(CARD_FAN_CENTER_X, CARD_FAN_CENTER_Y, 0.f) +
                        glm::vec3(CARD_FAN_CENTER_DIST*cos(ang_fst+glm::pi<float>()/2.f),CARD_FAN_CENTER_DIST*sin(ang_fst+glm::pi<float>()/2.f),0.f);
        m_data[i]->set_pos(pos);
        m_data[i]->set_rotY(0.f);
        m_data[i]->set_rotZ(ang_fst);
        ang_fst -= ang_between;
    }
}

void CardFan::on_render(VertexBatch* batch, bool renderHovered)
{
    for (int i = m_data.size()-1; i >= 0; i--)
    {
        if (renderHovered && i == m_hovered) continue;
        m_data[i]->on_render(batch, false, !m_data[i]->getType()->isType(m_highlighted));
    }
    if (renderHovered && m_hovered >= 0) m_data[m_hovered]->on_render(batch, true, !m_data[m_hovered]->getType()->isType(m_highlighted));
}
