#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texc;

out vec3 vertexColor;
out vec2 texcoord;

uniform mat4 projection;
uniform mat4 model;
uniform vec2 offsetTex;

void main()
{
	vertexColor = color;
	gl_Position = projection * model * vec4(position, 1.0);
	texcoord = vec2(texc.x + offsetTex.x , 1 - texc.y + offsetTex.y);
}