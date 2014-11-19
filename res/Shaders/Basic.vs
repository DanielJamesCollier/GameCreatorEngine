#version 440 core

in vec3 position;
in vec2 uv;
in vec3 normal;
in vec3 tangent;
in vec3 colour;

out vec3 fragmentPosition;
out vec2 fragmentUV;
out vec3 fragmentNormal;
out vec3 fragmentTangent;
out vec3 fragmentColour;

uniform mat4 mvp;


out mat4 proj;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{	
	gl_Position = mvp * vec4(position,1.0);
	
	fragmentPosition = position;
	fragmentUV		= uv;
	fragmentNormal	= normal;
	fragmentTangent	= tangent;
	fragmentColour	= colour;
	
	proj = mvp;
	
}

