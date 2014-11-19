#version 440 core

out vec4 frag_colour;

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;
in vec3 fragmentTangent;
in vec3 fragmentColour;

in mat4 proj;
uniform float time;

uniform sampler2D texture0;

void main()
{
	vec4 textureColor = texture(texture0, fragmentUV);
	frag_colour = vec4(cos(fragmentPosition.x  * 4.0 + time), cos(fragmentPosition.y * 8.0 + time), cos(fragmentPosition.z * 2.0 + time),1) * proj;

}