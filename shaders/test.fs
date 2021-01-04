#version 410 core
out vec4 FragColor;
uniform int color;
flat in vec4	fragment_color_f;
smooth in vec4	fragment_color_s;
in vec3 normals;
void main()
{
    // if (color == 1)
    //     FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    // else
    //     FragColor = vec4(0.0f, 0.5f, 0.2f, 1.0f);
    vec4 color = fragment_color_f;
    float grey = (0.2125 * color.x + 0.7154 * color.y + 0.0721 * color.z) / 3.0f;
    FragColor = vec4(normals, 1.0);//vec4(grey, grey, grey, 1);
}