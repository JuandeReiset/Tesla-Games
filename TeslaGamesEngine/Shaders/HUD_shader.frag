#version 330

in vec2 TexCoord;

out vec4 outColour;


uniform sampler2D theTexture;


void main()
{
	vec4 colour = texture(theTexture, TexCoord);

	if(colour.a < 0.1)
		discard;

	outColour = colour;
}