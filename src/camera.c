#include "camera.h"
#include "libft.h"
#include "libmath.h"

t_camera *camera_init()
{
	static t_camera * camera = NULL;
	if (!camera)
	{
		camera = ft_memalloc(sizeof(t_camera));
		camera->position = (t_vec3){0.0f, 0.0f, 3.0f};
		camera->target = (t_vec3){0.0f, 0.0f, 0.0f};
		camera->direction = ft_vec3_normalize(ft_vec3_substract(camera->position, camera->target));
		camera->up = (t_vec3){0.0f, 1.0f, 0.0f};
		camera->camera_right = ft_vec3_normalize(ft_vec3_cross_multiply(camera->up, camera->direction));
		camera->camera_up = ft_vec3_cross_multiply(camera->direction, camera->camera_right);
		camera->camera_front = (t_vec3){0.0f, 0.0f, -1.0f};
		camera->pitch = 0;
		camera->yaw = -90;
		camera->m_sesivity = 0.1f;
		camera->mouse = ft_memalloc(sizeof(t_mouse));
	}
	return camera;
}

void camera_update()
{	
	t_camera * cam; 
	t_vec3 front;

	cam = camera_init();
	front.x = cos(deg_to_rad(cam->yaw)) * cos(deg_to_rad(cam->pitch));
	front.y = sin(deg_to_rad(cam->pitch));
	front.z = sin(deg_to_rad(cam->yaw)) * cos(deg_to_rad(cam->pitch));
	cam->camera_front = ft_vec3_normalize(front); 
	cam->camera_right = ft_vec3_normalize(ft_vec3_cross_multiply(cam->camera_front, cam->up));  
	cam->camera_up= ft_vec3_normalize(ft_vec3_cross_multiply(cam->camera_right, cam->camera_front));
}

void camera_process(float xoffset, float yoffset)
{
	t_camera * cam; 

	cam = camera_init();
	xoffset *= cam->m_sesivity;
	yoffset *= cam->m_sesivity;
	cam->yaw += xoffset;
	cam->pitch += yoffset;
	if (cam->pitch > 89.0f)
		cam->pitch = 89.0f;
	if (cam->pitch < -89.0f)
		cam->pitch= -89.0f;
	camera_update();
}