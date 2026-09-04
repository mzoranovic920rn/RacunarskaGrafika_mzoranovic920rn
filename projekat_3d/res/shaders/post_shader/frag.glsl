#version 330
in vec2 pass_uv;
out vec4 final_colour;
uniform sampler2D uni_scena_tekstura;
uniform float uni_jacina_vinjete;

void main()
{
	vec4 boja = texture(uni_scena_tekstura, pass_uv);
	float udaljenost = distance(pass_uv, vec2(0.5, 0.5));
	float vinjeta = 1.0 - smoothstep(0.3, 0.75, udaljenost);
	vec3 konacna_boja = boja.rgb * mix(1.0, vinjeta, uni_jacina_vinjete);
	final_colour = vec4(konacna_boja, 1.0);
}
