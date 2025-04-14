#version 450 core

layout(triangles) in;

layout(line_strip, max_vertices = 2) out;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

uniform samplerCube uTexture;

in TESE_OUT{
    vec4 color;
    vec3 normal;
    vec3 texCoord;
} gs_in[];

void main() {
    vec4 noise = texture(uTexture, gs_in[0].texCoord);
    float n = 1.0 - noise.r; // Inversé pour correspondre à hauteur
    n = (n - 0.45) / (1.0 - 0.45);
    n = clamp(n, 0.0, 1.0);

    vec4 interpPos = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3;
    vec3 interpNormal = (gs_in[0].normal + gs_in[1].normal + gs_in[2].normal) / 3;
    vec4 interpNormal4 = vec4(interpNormal, 0.0) * uWorldTransform * uViewProj;
    if(n > 0.35 && n < 0.6)
    {
        gl_Position = interpPos;
        EmitVertex();
        gl_Position = interpPos +  interpNormal4;
        EmitVertex();
        EndPrimitive();
    }
}