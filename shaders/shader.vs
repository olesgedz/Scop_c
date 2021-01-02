// Vertex shader:
// ================
#version 400 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexture;


out vec3 FragPos;
// out vec3 Normal;
// out vec3 LightPos;
// out	vec2 TextureCoord;

uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

flat out vec4	fragment_color_f;
smooth out vec4	fragment_color_s;
out	vec2		texture_coordinates;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // FragPos = vec3(view * model * vec4(aPos, 1.0));
    // Normal = mat3(transpose(inverse(view * model))) * aNormal;
    // LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
    fragment_color_s = vec4(0,1,0,0);//vec4(position.y * 0.4f + 0.4f, position.z * 0.1 + position.y * 0.4f + 0.1f, 0.2f, 1.0f);
}
