#version 330

in vec3 pass_colour;

out vec4 final_colour;

void main()
{
	final_colour = vec4(pass_colour, 1.0f);
}

/// On je potpuno generican, uzme boju koju dobije i vrati je kao finalnu boju piksela
