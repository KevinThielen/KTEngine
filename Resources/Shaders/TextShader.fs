#version 330

uniform gsampler2DRect texture;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 finalColor;

void main()
{
    finalColor =  fragmentColor * texture2D(texture, fragmentUV);
    finalColor.a = texture2D(texture, fragmentUV).r;
}