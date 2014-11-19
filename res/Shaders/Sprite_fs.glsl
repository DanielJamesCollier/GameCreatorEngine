#version 440 core

out vec4 frag_colour;

in vec3 outPosition;
in vec2 outUV;
in vec3 outNormal;
in vec3 outTangent;
in vec4 outColour;

in mat4 proj;

uniform sampler2D texture0;

void main()
{

	vec4 texturePixel = texture(texture0, outUV);
	
	frag_colour = texturePixel * proj;

	//frag_colour = vec4(vec3(outUV,1.0),1.0) * proj;
	
	//frag_colour = texture(texture0,outUV);
}