#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
flat out vec4	fragment_color_f;
smooth out vec4	fragment_color_s;
out vec3 normals;
void main()
{  
  
   gl_Position =  projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
   fragment_color_f = vec4(aPos.y * 0.4f + 0.4f,
		aPos.z * 0.1 + aPos.y * 0.4f + 0.1f, 0.2f, 1.0f);
   fragment_color_s = vec4(aPos.y * 0.4f + 0.4f,
		aPos.z * 0.1 + aPos.y * 0.4f + 0.1f, 0.2f, 1.0f);
   normals = aNormals;
}