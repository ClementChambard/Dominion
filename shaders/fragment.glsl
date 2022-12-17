#version 130
precision mediump float;

in vec4 fragmentColor;
in vec2 fragmentTexCoords;

out vec4 color;

uniform sampler2D Texture;

void main()
{
    color = texture(Texture, fragmentTexCoords) * fragmentColor;
}
