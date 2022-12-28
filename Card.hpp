#ifndef CARD_H
#define CARD_H

#define CARD_SNAP_DISTANCE_SQ_TRESHOLD 0.1f
#define CARD_SNAP_ANGLE_TRESHOLD 0.01f
#define CARD_MOVEMENT_PROPORTION 4.f

#include "VertexBatch.hpp"
#include "CardsType/Type.hpp"
#include <glm/glm.hpp>

class Card
{
private:
    Type* m_type;

    glm::vec3 m_position{};
    glm::vec3 m_targetPosition{};

    float m_rotY = 0.f;
    float m_rotZ = 0.f;
    float m_targetRotY = 0.f;
    float m_targetRotZ = 0.f;
    bool m_recalculateRot = false;
    bool m_inAnim = false;
    glm::mat4 m_rotationMatrix;
    bool m_hovered = false;
    float m_hoveredAnimTime = 0.f;
public:
    Card(Type* type) : m_type(type), m_rotationMatrix(1.f) {}
    ~Card() = default;

    Type* getType() const { return m_type; }

    void set_pos(glm::vec3 const& p) { m_position = m_targetPosition = p; }
    void set_rotY(float r) { m_rotY = m_targetRotY = r; m_recalculateRot = true; }
    void set_rotZ(float r) { m_rotZ = m_targetRotZ = r; m_recalculateRot = true; }

    void set_hovered(bool h) { m_hovered = h; }

    void moveTo(glm::vec3 const& p) { m_targetPosition = p; m_inAnim = true; }
    void rotateYTo(float r) { m_targetRotY = r; m_inAnim = true; }
    void rotateZTo(float r) { m_targetRotZ = r; m_inAnim = true; }

    bool isInAnim() const { return m_inAnim; }

    void on_tick();
    void on_render(VertexBatch* batch, bool hovered = false);
};


#endif 



