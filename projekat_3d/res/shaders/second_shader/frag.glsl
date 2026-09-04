#version 330
in vec3 pass_colour;
in vec3 pass_position;
out vec4 final_colour;
uniform float uni_pod_sara;
uniform float uni_zid_sara;
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

float izracunaj_oblak(vec2 pos)
{
	float val = 0.0;
	val += sin(pos.x * 2.0 + pos.y * 0.5);
	val += sin(pos.x * 3.1 - pos.y * 0.9) * 0.5;
	val += sin(pos.x * 1.1 + pos.y * 1.7) * 0.3;
	val += sin(pos.x * 5.3 + pos.y * 4.8) * 0.2;
	return val / 1.8;
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
		float ambient = 0.7;
		float diffuse = max(dot(perturbovana_normala, normalize(-uni_light_dir)), 0.0);
		float light = ambient + diffuse * 0.55;
		float faktor = (h + 1.0) * 0.5;
		vec3 boja1 = vec3(0.9f, 0.9f, 0.9f);
		vec3 boja2 = vec3(0.18f, 0.34f, 0.41f);
		vec3 sara_boja = mix(boja1, boja2, faktor) * light;
		final_colour = vec4(sara_boja, 1.0f);
	}
	else if (uni_zid_sara > 0.5)
	{
		vec2 pos = pass_position.xy;
		float epsilon = 0.1;
		float h = izracunaj_oblak(pos);
		float h_dx = izracunaj_oblak(pos + vec2(epsilon, 0.0));
		float h_dy = izracunaj_oblak(pos + vec2(0.0, epsilon));
		float jacina = 3.0;
		float px = clamp(-(h_dx - h) * jacina, -0.4, 0.4);
		float py = clamp(-(h_dy - h) * jacina, -0.4, 0.4);
		vec3 perturbovana_normala = normalize(vec3(px, py, -1.0));
		float ambient = 0.75;
		float diffuse = max(dot(perturbovana_normala, normalize(-uni_light_dir)), 0.0);
		float light = ambient + diffuse * 0.55;
		float faktor = clamp((h * 1.1 + 1.0) * 0.5, 0.0, 1.0);
		vec3 boja1 = vec3(0.95, 0.95, 0.97);
        vec3 boja2 = vec3(0.45, 0.55, 0.62);
		//vec3 boja1 = vec3(0.55, 0.55, 0.62);
		//vec3 boja2 = vec3(0.75, 0.78, 0.85);
		vec3 zid_boja = mix(boja1, boja2, faktor) * light;
		final_colour = vec4(zid_boja, 1.0);
	}
	else
	{
		final_colour = vec4(pass_colour, 1.0f);
	}
}
