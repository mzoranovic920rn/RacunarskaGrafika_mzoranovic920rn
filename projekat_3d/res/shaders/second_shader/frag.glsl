#version 330
in vec3 pass_colour;
in vec3 pass_position;
out vec4 final_colour;
uniform float uni_pod_sara;
uniform vec3 uni_light_dir;

float izracunaj_visinu(vec2 pos)
{
	float cx = 0.0;
	float cz = 3.0;
	float dx = pos.x - cx;
	float dz = pos.y - cz;
	float udaljenost = sqrt(dx * dx + dz * dz);
	float ugao = atan(dz, dx);
	return sin(udaljenost * 1.0 + ugao * 2.0);
}

void main()
{
	if (uni_pod_sara > 0.5)
	{


		vec2 pos = pass_position.xz;
		float epsilon = 0.1;

		float h = izracunaj_visinu(pos);
		float h_dx = izracunaj_visinu(pos + vec2(epsilon, 0.0));
		float h_dz = izracunaj_visinu(pos + vec2(0.0, epsilon));

		float jacina = 1.5;
		vec3 perturbovana_normala = normalize(vec3(-(h_dx - h) * jacina, 1.0, -(h_dz - h) * jacina));

		float ambient = 0.45;
		float diffuse = max(dot(perturbovana_normala, normalize(-uni_light_dir)), 0.0);
		float light = ambient + diffuse * 0.55;

		float faktor = (h + 1.0) * 0.5;
		vec3 boja1 = vec3(0.9f, 0.9f, 0.9f);
		vec3 boja2 = vec3(0.18f, 0.34f, 0.41f);
		vec3 sara_boja = mix(boja1, boja2, faktor) * light;

		final_colour = vec4(sara_boja, 1.0f);
	}
	else
	{
		final_colour = vec4(pass_colour, 1.0f);
	}
}
