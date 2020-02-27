#version 330

in vec2 TexCoord;

out vec4 OutColor;

uniform sampler2D theTexture;

void main()
{
	vec4 color = texture(theTexture, TexCoord);

	OutColor = color;
}