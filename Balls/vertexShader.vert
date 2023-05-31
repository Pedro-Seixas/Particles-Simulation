#version 330 core

uniform sampler2D positionsTexture;
uniform vec2 mousePosition;

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

void main()
{
    ivec2 texSize = textureSize(positionsTexture, 0);
    vec2 texCoord = vertexPosition / texSize;

    vec4 position = texture2D(positionsTexture, texCoord);
    vec2 particlePosition = position.xy;

    vec2 distance = particlePosition - mousePosition;
    float distSquared = dot(distance, distance);

    float distanceLimit = 1.0;
    float escapeIntensity = 100.0 / distSquared;

    if (distSquared < distanceLimit)
    {
        escapeIntensity = 0.0;
    }

    vec2 acceleration = distance * escapeIntensity;

    position.xy += acceleration;

    gl_Position = vec4(position.xy, 0.0, 1.0);
    fragmentColor = vertexColor;
}