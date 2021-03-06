/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:14:12 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 23:17:33 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft.h"
#include "libmath.h"
#include "scop.h"

t_camera			*camera_init(void)
{
	static t_camera *camera = NULL;

	if (!camera)
	{
		camera = ft_memalloc(sizeof(t_camera));
		camera->position = (t_vec3){0.0f, 0.0f, 3.0f};
		camera->target = (t_vec3){0.0f, 0.0f, 0.0f};
		camera->direction = ft_vec3_normalize(
		ft_vec3_substract(camera->position, camera->target));
		camera->up = (t_vec3){0.0f, 1.0f, 0.0f};
		camera->camera_right = ft_vec3_normalize(
		ft_vec3_cross_multiply(camera->up, camera->direction));
		camera->camera_up = ft_vec3_cross_multiply(camera->direction,
		camera->camera_right);
		camera->camera_front = (t_vec3){0.0f, 0.0f, -1.0f};
		camera->pitch = 0;
		camera->yaw = -90;
		camera->m_sesivity = 0.1f;
		camera->mouse = ft_memalloc(sizeof(t_mouse));
		camera->mouse->last_x = SCR_WIDTH / 2.0f;
		camera->mouse->last_y = SCR_HEIGHT / 2.0f;
	}
	return (camera);
}

void				camera_update(void)
{
	t_camera	*cam;
	t_vec3		front;

	cam = camera_init();
	front.x = cos(deg_to_rad(cam->yaw)) * cos(deg_to_rad(cam->pitch));
	front.y = sin(deg_to_rad(cam->pitch));
	front.z = sin(deg_to_rad(cam->yaw)) * cos(deg_to_rad(cam->pitch));
	cam->camera_front = ft_vec3_normalize(front);
	cam->camera_right = ft_vec3_normalize(
	ft_vec3_cross_multiply(cam->camera_front, cam->up));
	cam->camera_up = ft_vec3_normalize(ft_vec3_cross_multiply(cam->camera_right,
	cam->camera_front));
}

void				camera_process(float xoffset, float yoffset)
{
	t_camera *cam;

	cam = camera_init();
	xoffset *= cam->m_sesivity;
	yoffset *= cam->m_sesivity;
	cam->yaw += xoffset;
	cam->pitch += yoffset;
	if (cam->pitch > 89.0f)
		cam->pitch = 89.0f;
	if (cam->pitch < -89.0f)
		cam->pitch = -89.0f;
	camera_update();
}
