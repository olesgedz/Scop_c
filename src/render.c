/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:35:19 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:38:40 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	upload_texture(t_model *model)
{
	glGenTextures(1, &model->texture.id);
	glBindTexture(GL_TEXTURE_2D, model->texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model->texture.width,
	model->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, model->texture.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	model->texture_exists = 1;
}

void upload_model(t_model *model)
{
	glGenBuffers(1, &model->vbo_vertices);
	glGenVertexArrays(1, &model->voa);
	glBindVertexArray(model->voa);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, model->num_vertices * sizeof(float), model->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
						  (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, model->num_normals * sizeof(float),
				model->normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}


void renderer(t_gl *gl, t_model *model, t_scene *scene)
{
	t_mat4 model_matrix;
	while (!glfwWindowShouldClose(gl->window))
	{
		processInput(gl->window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_time(scene);
		scene->model_matrix = ft_mat4_identity_matrix();
		model_matrix = ft_mat4_multiply_mat4(ft_mat4_translation_matrix(model->center), model_matrix);
		model_matrix = ft_mat4_multiply_mat4(scene->model_matrix, ft_mat4_rotation_matrix((t_vec3){0,1,0},(float)glfwGetTime() * 1.0f));
		scene->view = ft_look_at(scene->camera->position, ft_vec3_sum(scene->camera->position,scene->camera->camera_front), scene->camera->camera_up);
		model->shader->use(model->shader);
		glBindVertexArray(model->voa);
		model->shader->set_int(model->shader, "color", 0);
		model->shader->set_int(model->shader, "grey", model->grey);
		model->shader->set_int(model->shader, "smoothc", model->smooth);
		model->shader->set_int(model->shader, "normal_color", model->normal);
		model->shader->set_int(model->shader, "texture_mode", model->texture_mode);
		model->shader->set_int(model->shader, "light_color", model->light);
		model->shader->set_mat4(model->shader, "model", &model_matrix);
		model->shader->set_mat4(model->shader, "view", &scene->view);
		model->shader->set_mat4(model->shader, "projection", &scene->proj);
		model->shader->set_vec3(model->shader, "lightPos", &scene->light_pos);
		glBindTexture(GL_TEXTURE_2D, model->texture.id);
		glDrawArrays(GL_TRIANGLES, 0, model->num_vertices);
		glBindVertexArray(0);
		glfwSwapBuffers(gl->window);
		glfwPollEvents();
	}
}