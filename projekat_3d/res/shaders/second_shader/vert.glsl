#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;

out vec3 pass_colour;

uniform mat4 uni_M;
uniform mat4 uni_VP;
uniform vec3 uni_normal;
uniform vec3 uni_light_dir;

void main()
{
	vec4 world_position = uni_M * vec4(position, 1.0);
	gl_Position = uni_VP * world_position;

	float ambient = 0.45;
	float diffuse = max(dot(normalize(uni_normal), normalize(-uni_light_dir)), 0.0);
	float light = ambient + diffuse * 0.55;

	pass_colour = colour * light;
}
