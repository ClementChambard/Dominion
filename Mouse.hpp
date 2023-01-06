#ifndef MOUSE_H
#define MOUSE_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class Mouse {
    public:
        Mouse() = delete;
        ~Mouse() = delete;


        static void processEvent(SDL_Event& event);

        static void setWindowSize(float w, float h);

        static bool button() { return m_leftDown; }
        static bool press() { return m_leftPressed; }
        static bool release() { return m_leftReleased; }

        static glm::vec3 toWorld(float x, float y, float h, glm::vec3 C);
        static glm::vec3 toWorldCurrent(float h, glm::vec3 C);
        static glm::vec2 getpos() { return glm::vec2(m_screenX, m_screenY); }
        static glm::vec2 getposNormalized(){ return glm::vec2(m_screenX*2/WINDOW_WIDTH-1, -m_screenY*2/WINDOW_HEIGHT+1); }
        static glm::vec2 getWindowSize(){ return glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT); }
        static void setInvPV(glm::mat4 const& inv_p_v) { m_inv_p_v = inv_p_v; }

    private:
        static float WINDOW_WIDTH;
        static float WINDOW_HEIGHT;
        static float m_screenX;
        static float m_screenY;
        static bool m_leftDown;
        static bool m_leftPressed;
        static bool m_leftReleased;
        static glm::mat4 m_inv_p_v;

};

#endif // MOUSE_H