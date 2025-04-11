#version 450 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 4) out; // Adapté pour des quads

uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uCameraPos;

in TESE_OUT{
    vec4 color;
    vec3 normal;
    vec3 texCoord;
} gs_in[];

out TESE_OUT {
    vec4 color;
    vec3 normal;
    vec3 texCoord;
} gs_out;

out vec2 gTexCoord;

void main() {

}