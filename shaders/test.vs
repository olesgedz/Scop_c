#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 projection;
void main()
{
	mat4 a = mat4(1);
   gl_Position =  model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}