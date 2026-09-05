#version 330
in vec2 pass_uv;
out vec4 final_colour;

uniform sampler2D uni_plocica_tekstura;

void main()
{
	final_colour = texture(uni_plocica_tekstura, pass_uv);
}
