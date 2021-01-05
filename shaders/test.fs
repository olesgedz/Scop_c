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

void main()
{
    vec4 color = fragment_color_f;
    if (grey)
    {
        float greyc = (0.2125 * color.x + 0.7154 * color.y + 0.0721 * color.z) / 3.0f;
        FragColor =   vec4(grey, grey, grey, 1);
    }
    else
    {
      vec2 test = vec2(pos.x,pos.y);
      vec3 norm = normalize(normals);
      vec3 lightDir = normalize(light - vec3(pos)); 
      float diff = max(dot(norm, lightDir), 0.0);
      FragColor = diff * texture(texture1, uv);
    }
    //     FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // else
    //     FragColor = vec4(0.0f, 0.5f, 0.2f, 1.0f);
 
}