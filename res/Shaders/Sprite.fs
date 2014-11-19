#version 440 core

out vec4 frag_colour;

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;
in vec3 fragmentTangent;
in vec4 fragmentColour;

in mat4 proj;

uniform sampler2D texture0;

uniform float timex;

void main()
{

	vec4 texturePixel = texture(texture0, fragmentUV);
	
	frag_colour = vec4(cos(fragmentPosition.x  * 2.0 + timex) + 0.5, cos(fragmentPosition.y * 2.0 + timex), cos(fragmentPosition.z * 2.0 + timex),1) * texturePixel * proj;
}