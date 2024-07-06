#version 430

in vec3 vertexColor;
in vec2 texcoord;

uniform sampler2D texBuffer;
uniform vec2 offsets;

out vec4 color;

void main()
{
	color = texture(texBuffer, texcoord + offsets);

}