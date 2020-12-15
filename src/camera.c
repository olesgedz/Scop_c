#include "camera.h"
#include "libft.h"

t_camera *camera_init()
{
	t_camera * camera;
	camera = ft_memalloc(sizeof(t_camera));
	camera->position = (t_vec3){0.0f, 0.0f, 3.0f};
	camera->target = (t_vec3){0.0f, 0.0f, 0.0f};
	camera->direction = ft_vec3_normalize(ft_vec3_substract(camera->position, camera->target));
	camera->up = (t_vec3){0.0f, 1.0f, 0.0f};
	camera->camera_right = ft_vec3_normalize(ft_vec3_cross_multiply(camera->up, camera->direction));
	camera->camera_up = ft_vec3_cross_multiply(camera->direction, camera->camera_right);
	camera->camera_front = (t_vec3){0.0f, 0.0f, -1.0f};
	return camera;
}