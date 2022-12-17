#version 130
precision mediump float;

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexTexCoords;

out vec4 fragmentColor;
out vec2 fragmentTexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1.0);

    fragmentColor = vertexColor;
    fragmentTexCoords = vertexTexCoords;
}
