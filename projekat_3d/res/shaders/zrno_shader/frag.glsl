#version 330
in vec2 pass_uv;
out vec4 final_colour;
uniform sampler2D uni_scena_tekstura;
uniform float uni_vreme;
uniform float uni_jacina_zrna;

float nasumicno(vec2 st)
{
	return fract(sin(dot(st, vec2(12.9898, 78.233))) * 43758.5453123);
}

void main()
{
	vec3 boja = texture(uni_scena_tekstura, pass_uv).rgb;
	float zrno = nasumicno(pass_uv * 743.0 + uni_vreme) - 0.5;
	vec3 konacna_boja = boja + zrno * uni_jacina_zrna;
	final_colour = vec4(konacna_boja, 1.0);
}
