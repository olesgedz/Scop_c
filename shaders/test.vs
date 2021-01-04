#version 410 core
# define PI 3.14159265359

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
flat out vec4	fragment_color_f;
smooth out vec4	fragment_color_s;
out vec3 normals;
out vec2 uv;
out vec4 pos;
vec2	cylinder_mapping()
{
	float	u;
	float	v;

	u = 0.5 + atan(aPos.z, aPos.x) / PI * 0.5;
	v = aPos.y / 10.0;
	return (vec2(u, v) * 15);
}

void main()
{  
  
   gl_Position =  projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
   fragment_color_f = vec4(aPos.y * 0.4f + 0.4f,
		aPos.z * 0.1 + aPos.y * 0.4f + 0.1f, 0.2f, 1.0f);
   fragment_color_s = vec4(aPos.y * 0.4f + 0.4f,
		aPos.z * 0.1 + aPos.y * 0.4f + 0.1f, 0.2f, 1.0f);
   normals = aNormals;
   uv = cylinder_mapping();
   pos = gl_Position;
}