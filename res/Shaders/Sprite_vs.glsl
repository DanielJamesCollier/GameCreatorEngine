#version 440 core

in vec3 position;
in vec2 uv;
in vec3 normal;
in vec3 tangent;
in vec4 colour;

out vec3 outPosition;
out vec2 outUV;
out vec3 outNormal;
out vec3 outTangent;
out vec4 outColour;

uniform mat4 mvp;

out mat4 proj;

void main()
{
	gl_Position = mvp * vec4(position,1.0);
	
	outPosition = position;
	outUV		= uv;
	outNormal	= normal;
	outTangent	= tangent;
	outColour	= colour;
	
	proj = mvp;
	
}