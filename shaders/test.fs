#version 410 core
out vec4 FragColor;
flat in vec4	fragment_color_f;
smooth in vec4	fragment_color_s;
in vec3 normals;
in vec2				uv;
in vec4 pos;
in vec3 light;

uniform sampler2D texture1;
uniform bool grey;
uniform bool smoothc;
uniform bool texture_mode;
uniform bool normal_color;
uniform bool light_color;

void main()
{
    vec4 color = fragment_color_f;
    if (smoothc)
      color = fragment_color_s;
    if (texture_mode)
      color = texture(texture1, uv);
    if (grey)
    {
        float greyc = (0.2125 * fragment_color_f.x + 0.7154 * fragment_color_f.y + 0.0721 * fragment_color_f.z) / 3.0f;
        color =   vec4(greyc, greyc, greyc, 1);
    }
     if (light_color)
    {
      vec3 norm = normalize(normals);
      vec3 lightDir = normalize(light - vec3(pos)); 
      float diff = max(dot(norm, lightDir), 0.0);
      color = diff * color;
    }
    if (normal_color)
      color = vec4(normals, 1.0f);
        
    FragColor = color;
 
}