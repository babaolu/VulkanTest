#version 460

layout(location = 0) out vec3 fragColor;

vec2 square[] = {
     vec2(-0.5, -0.5),
     vec2(0.5, -0.5),
     vec2(0.5, 0.5),
     vec2(-0.5, 0.5)
};

void main()
{
	/*gl_Position = vec4(square[gl_VertexIndex], 0, 1);
	float angle = radians(90 / 4.0) * gl_VertexIndex;
	fragColor = vec3(cos(angle), tan(angle), sin(angle));

	if (gl_VertexIndex == 0)
	{
		gl_Position = vec4(0, 0, 0, 1);
		fragColor = vec3(1.0, 1.0, 1.0);
	} else {*/
       float angle = radians((gl_VertexIndex) * 0.5);
       gl_Position = vec4(0.5 * sin(angle), 0.5 * cos(angle), 0, 1);
       float col_pos = radians((gl_VertexIndex) / 8.0);
       float mid = tan(col_pos);
       fragColor = vec3(cos(col_pos), (mid <= 1) ? mid : (1 / mid),
       		   	sin(col_pos));
	//}
}