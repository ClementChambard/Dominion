#include "SpriteFont.hpp"
#include "Mouse.hpp"
#include <fstream>
#include <algorithm>

SpriteFont* SpriteFont::last_created_instance = nullptr;

SpriteFont::SpriteFont(std::string filename) {
    fontBatch = new VertexBatch();
    std::ifstream file(filename);

    std::string texture_file;
    file >> texture_file;
    font_atlas = new Texture(texture_file);

    while (!file.eof()) {
        SpriteFont::Glyph g;
        file >> g;
        glyphs.push_back(g);
    }
    glyphs[0].c = ' ';

    file.close();
    last_created_instance = this;
}

SpriteFont::~SpriteFont() {
    delete fontBatch;
    delete font_atlas;
}

float calcTextSize(std::string text, std::vector<SpriteFont::Glyph> const& glyphs, float s)
{
    float size = 0.f;
    for (size_t i = 0; i < text.size(); i++) {
        char c = text[i];
        auto G = std::find_if(glyphs.begin(), glyphs.end(), [c](SpriteFont::Glyph g){ return g.c == c; });
        if (G == glyphs.end()) continue;
        if (i == text.size()-1) size += G->size.x * s;
        else size += G->x_advance * s;
    }
    return size;
}

void SpriteFont::renderText(std::string text, glm::vec2 pos, glm::vec2 charSize, glm::vec<4, uint8_t> col)
{
    glm::vec2 ws = Mouse::getWindowSize();
    charSize.y *= (ws.x/ws.y);
    float totalWidth = calcTextSize(text, glyphs, charSize.x);
    float x = pos.x -totalWidth / 2.f;
    std::vector<Glyph>::iterator G;
    if (text.size() > 0) if ((G = std::find_if(glyphs.begin(), glyphs.end(), [text](Glyph g){ return g.c == text[0]; })) != glyphs.end()) x += G->size.x/2.f*charSize.x;
    float pc = 0.f;
    for (char c : text) {
        auto G = std::find_if(glyphs.begin(), glyphs.end(), [c](Glyph g){ return g.c == c; });
        if (G == glyphs.end()) continue;
        fontBatch->draw_rectangle(x+G->offset.x, pos.y+G->offset.y, 0, G->size.x*charSize.x, G->size.y*charSize.y, glm::mat4(1.f), G->uvs, col);
        x += G->x_advance*charSize.x;
        pc += 1.f/text.size();
    }
}

void SpriteFont::renderAllText() {
    fontBatch->finish_adding();
    fontBatch->render(font_atlas);
    fontBatch->clear_vertices();
}

std::istream& operator>>(std::istream& l, SpriteFont::Glyph& r) {
    return (l >> r.c >> r.size.x >> r.size.y >> r.offset.x >> r.offset.y >> r.uvs.x >> r.uvs.y >> r.uvs.z >> r.uvs.w >> r.x_advance);
}
