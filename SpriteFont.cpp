#include "SpriteFont.hpp"

VertexBatch* SpriteFont::fontBatch = nullptr;

glm::vec4 getCharUV(std::string chars, char c, float charNbH, float charNbV)
{
    size_t idInChars = 0;
    for (auto cc : chars) { if (c == cc) break; idInChars++; }
    if (idInChars == chars.size()) return {0,0,0,0};
    int x = idInChars % (int)charNbH;
    int y = idInChars / (int)charNbH;
    float xs = 1/charNbH;
    float ys = 1/charNbV;
    return {x*xs,y*ys,(x+1)*xs,(y+1)*ys};
}

void SpriteFont::renderText(std::string text, glm::vec2 pos, glm::vec2 charSize)
{
    if (!fontBatch) fontBatch = new VertexBatch();
    float totalWidth = text.size() * charSize.x;
    float x = -totalWidth / 2.f;
    for (char c : text) {
        fontBatch->draw_rectangle(x, pos.y, 0, charSize.x, charSize.y, glm::mat4(1.f), getCharUV(chars, c, charNbH, charNbV));
        x += charSize.x;
    }
}

void SpriteFont::renderAllText() {
    if (!fontBatch) fontBatch = new VertexBatch();
    fontBatch->finish_adding();
    fontBatch->render(font_atlas);
    fontBatch->clear_vertices();
}
