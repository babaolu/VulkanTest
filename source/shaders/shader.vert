#version 460

layout(location = 0) out vec3 fragColor;

void main()
{
	if (gl_VertexIndex == 0)
	{
		gl_Position = vec4(0, 0, 0, 1);
		fragColor = vec3(1.0, 1.0, 1.0);
	} else
	{
		float angle = radians((gl_VertexIndex - 1) * 0.5);
		gl_Position = vec4(0.5 * sin(angle), 0.5 * cos(angle), 0, 1);

		float col_pos = radians((gl_VertexIndex - 1) / 8.0);
		fragColor = vec3(cos(col_pos), tan(col_pos), sin(col_pos));
	}
}