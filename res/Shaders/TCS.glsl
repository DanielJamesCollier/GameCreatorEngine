#version 440

layout (vertices = 3) out;

void main(void)
{

	if(gl_InvocationID == 0)
	{
		glTessLevelInner[0] = 5.0;
		glTessLevelOuter[0] = 5.0;
		glTessLevelOuter[2] = 5.0;
		glTessLevelOuter[3] = 5.0;
	}
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}