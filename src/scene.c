/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:34:12 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:42:13 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "scene.h"

t_scene			*scene_create(void)
{
	static t_scene *scene = NULL;

	if (!scene)
	{
		scene = ft_memalloc_s(sizeof(t_scene));
	}
	return (scene);
}

t_scene			*scene_init(t_scene *scene, t_gl *gl, t_model *model)
{
	glfwSetCursorPosCallback(gl->window, mouse_callback);
	glEnable(GL_DEPTH_TEST);
	scene->light_pos = (t_vec3){0, 0, 3};
	scene->proj = set_projection_matrix();
	scene->view = ft_mat4_identity_matrix();
	scene->camera = camera_init();
	scene->model = model;
	scene->gl = gl;
	scene->last_time = 0;
	scene->last_press = 0;
	return (scene);
}
