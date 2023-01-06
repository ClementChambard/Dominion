#include "VertexBatch.hpp"
#ifndef Button_H_
#define Button_H_

class Button
{
private:
    glm::vec4 uv;
    glm::vec4 hover;
    glm::vec2 pos;
    glm::vec2 size;

public:
    Button(glm::vec4 uvnormal, glm::vec4 hover, glm::vec2 pos, glm::vec2 size);
    ~Button()=default;
    void onUpdate(VertexBatch* batch);
    bool isHovered();

  
};














#endif // Button_H_