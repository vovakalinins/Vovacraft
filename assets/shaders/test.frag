#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 VertexColor;

// texture samplers
uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, TexCoord);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor * vec4(VertexColor, 1.0);
}
