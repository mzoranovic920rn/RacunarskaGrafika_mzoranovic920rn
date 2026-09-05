#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

uniform mat4 uni_M;
uniform mat4 uni_VP;

out vec2 pass_uv;

void main()
{
	gl_Position = uni_VP * uni_M * vec4(position, 1.0);
	pass_uv = uv;
}
