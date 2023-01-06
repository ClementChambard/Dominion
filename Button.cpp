#include "Button.hpp"
#include "Mouse.hpp"

Button::Button(glm::vec4 uvnormal, glm::vec4 hover, glm::vec2 pos, glm::vec2 size)
{
    this->hover = hover;
    this->uv = uvnormal;
    this->pos = pos;
    this->size = size;
}

void Button::onUpdate(VertexBatch* batch)
{
 
    batch->draw_rectangle(pos.x,pos.y,0, size.x,size.y, glm::mat4(1.f),isHovered() ? this->hover : this->uv);

}
bool Button::isHovered()
{
    glm::vec2 mouse = Mouse::getposNormalized();
    return mouse.x > pos.x-size.x/2 && mouse.x < pos.x + size.x/2 && mouse.y > pos.y-size.y/2 && mouse.y < pos.y + size.y/2;
}