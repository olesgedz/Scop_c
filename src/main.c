/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:50:09 by olesgedz          #+#    #+#             */
/*   Updated: 2021/01/06 17:05:09 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "scop.h"
#include "mesh.h"
#include "libmath.h"
#include "camera.h"
#include "bmp.h"
#include "scene.h"

int					main(int argc, char **argv)
{
	t_gl		gl;
	t_model		*model;
	t_scene		*scene;

	check_params(argc, argv);
	init_gl(SCR_HEIGHT, SCR_HEIGHT, &gl);
	model = model_init();
	load_obj(model, argv[1]);
	model->shader = mgl_shader_create("./shaders/test.vs", "./shaders/test.fs");
	if (argc == 3)
	{
		load_bmp(model, argv[2]);
		model_bind_texture(model);
		upload_texture(model);
	}
	upload_model(model);
	scene = scene_init(scene_create(), &gl, model);
	renderer(&gl, model, scene);
	glDeleteVertexArrays(1, &model->voa);
	glDeleteBuffers(1, &model->vbo_vertices);
	glDeleteBuffers(1, &model->vbo_normals);
	glfwTerminate();
	return (0);
}

static void			process_input_time(GLFWwindow *window, t_scene *scene)
{
	if ((scene->current_frame - scene->last_press) > 0.07)
	{
		scene->last_press = scene->current_frame;
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			key_switch(&scene->model->lines);
			if (scene->model->lines == 1)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			key_switch(&scene->model->grey);
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
			key_switch(&scene->model->smooth);
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
			key_switch(&scene->model->texture_mode);
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
			key_switch(&scene->model->light);
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			key_switch(&scene->model->normal);
	}
}

void				process_input_pr(GLFWwindow *window,
	t_camera *camera, float camera_speed)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position,
		ft_vec3_scalar_multiply(camera->camera_front, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position,
		ft_vec3_scalar_multiply(camera->camera_front, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position,
		ft_vec3_scalar_multiply(ft_vec3_normalize(
		ft_vec3_cross_multiply(camera->camera_front,
		camera->camera_up)), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position,
	ft_vec3_scalar_multiply(ft_vec3_normalize(ft_vec3_cross_multiply(
	camera->camera_front, camera->camera_up)), camera_speed));
}

void				process_input(GLFWwindow *window)
{
	t_camera	*camera;
	t_scene		*scene;
	float		camera_speed;

	camera = camera_init();
	scene = scene_create();
	camera_speed = 0.05f;
	process_input_pr(window, camera, camera_speed);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		exit(0);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position,
	ft_vec3_scalar_multiply(camera->camera_up, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position,
	ft_vec3_scalar_multiply(camera->camera_up, camera_speed));
	process_input_time(window, scene);
}

void				mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_camera	*cam;
	float		xoffset;
	float		yoffset;

	(void)window;
	cam = camera_init();
	if (cam->mouse->first_mouse)
	{
		cam->mouse->last_x = xpos;
		cam->mouse->last_y = ypos;
		cam->mouse->first_mouse = 0;
	}
	xoffset = xpos - cam->mouse->last_x;
	yoffset = cam->mouse->last_y - ypos;
	cam->mouse->last_x = xpos;
	cam->mouse->last_y = ypos;
	camera_process(xoffset, yoffset);
}
