#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;
uniform float time;
uniform float screenWidth;
uniform float screenHeight;

void main()
{    
    float sampledAlpha = texture(text, TexCoords).r;
    
    if (sampledAlpha < 0.2)
        discard;

    if(time > 2000 && time < 2700)
    {
        float speed = 2.0;
        float width = 100.0;
        float slope = -0.5;

        // Position du pixel actuel
        float x = gl_FragCoord.x;
        float y = gl_FragCoord.y;

        // Position de la lame
        float center = mod(time * speed, screenWidth + width) - width; 
        // ---> commence à -width puis avance

        // Calcul position inclinée
        float bladePosition = x + y * slope;

        float distance = abs(bladePosition - center);
        float glow = smoothstep(width, 0.0, distance);

        vec3 baseColor = textColor.rgb;
        vec3 finalColor = baseColor + glow * 0.5;
        color = vec4(finalColor, textColor.a * sampledAlpha);
    }
    else
    {
        color = vec4(textColor) * sampledAlpha;
    }
}