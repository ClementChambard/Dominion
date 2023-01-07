#include "Mouse.hpp"


float Mouse::WINDOW_WIDTH = 0.f;
float Mouse::WINDOW_HEIGHT = 0.f;
float Mouse::m_screenX = 0.f;
float Mouse::m_screenY = 0.f;
bool Mouse::m_leftDown = false;
bool Mouse::m_leftPressed = false;
bool Mouse::m_leftReleased = false;
glm::mat4 Mouse::m_inv_p_v = glm::mat4(1.f);
glm::vec3 Mouse::m_cam_pos = glm::vec3(0.f, 0.f, 0.f);

void Mouse::resetState() {
    m_leftPressed = false;
    m_leftReleased = false;
}

void Mouse::processEvent(SDL_Event &event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
            m_screenX = event.motion.x;
            m_screenY = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_leftDown = true;
            m_leftPressed = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_leftDown = false;
            m_leftReleased = true;
            break;
    }
}

void Mouse::setWindowSize(float w, float h)
{
    WINDOW_WIDTH = w;
    WINDOW_HEIGHT = h;
}

glm::vec3 Mouse::toWorldCurrent(float h)
{
    return toWorld(m_screenX, m_screenY, h);
}

glm::vec3 Mouse::toWorld(float x, float y, float h)
{
    glm::vec4 near = glm::vec4((x - WINDOW_WIDTH/2.f) / (WINDOW_WIDTH/2.f), -1*(y - WINDOW_HEIGHT/2.f) / (WINDOW_HEIGHT/2.f), -1, 1.0);
    glm::vec4 far = glm::vec4((x - WINDOW_WIDTH/2.f) / (WINDOW_WIDTH/2.f), -1*(y - WINDOW_HEIGHT/2.f) / (WINDOW_HEIGHT/2.f), 1, 1.0);
    glm::vec4 nearResult = m_inv_p_v*near;
    glm::vec4 farResult = m_inv_p_v*far;
    nearResult /= nearResult.w;
    farResult /= farResult.w;
    glm::vec3 T = m_cam_pos + glm::vec3(farResult - nearResult);
    if (m_cam_pos.z == T.z) return m_cam_pos;
    x = m_cam_pos.x - (T.x-m_cam_pos.x)*(m_cam_pos.z-h)/(T.z-m_cam_pos.z);
    y = m_cam_pos.y - (T.y-m_cam_pos.y)*(m_cam_pos.z-h)/(T.z-m_cam_pos.z);
    return {x, y, h};
}
