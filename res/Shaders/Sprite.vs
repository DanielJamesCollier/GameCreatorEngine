#version 440 core

in vec3 position;
in vec2 uv;
in vec3 normal;
in vec3 tangent;
in vec4 colour;

out vec3 fragmentPosition;
out vec2 fragmentUV;
out vec3 fragmentNormal;
out vec3 fragmentTangent;
out vec4 fragmentColour;

uniform mat4 mvp;

out mat4 proj;

void main()
{
	gl_Position = mvp * vec4(position,1.0);
	
	fragmentPosition = position;
	fragmentUV		= vec2(uv.x, 1.0 - uv.y);
	fragmentNormal	= normal;
	fragmentTangent	= tangent;
	fragmentColour	= colour;
	
	proj = mvp;
}