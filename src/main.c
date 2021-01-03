/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:50:09 by olesgedz          #+#    #+#             */
/*   Updated: 2020/03/10 21:15:48 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "scop.h"
#include "mesh.h"
#include "libmath.h"
#include "camera.h"
#include "bmp.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


t_mat4 set_projection_matrix()
{
	float s;
	float far;
	float near;
	float fov = 70.f;
	t_mat4 ret = ft_mat4_zero();
	far = 100.f;
	near = 0.1f;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	ret = ft_mat4_identity_matrix();
	ret.matrix[0][0] = s / ((float)SCR_WIDTH / (float)SCR_HEIGHT);
	ret.matrix[1][1] = s;
	ret.matrix[2][2] = -(far + near) / (far - near);
	ret.matrix[2][3] = -1;
	ret.matrix[3][2] = -2 * far * near / (far - near);
	return (ret);
}

void load_texture( t_model *model, char * filename)
{
	if (filename)
	{
		model->texture.data = parse_bmp(filename, &model->texture.width, &model->texture.height);
		if (model->texture.data)
		{
			glGenTextures(1, &model->texture.id);
  			glBindTexture(GL_TEXTURE_2D, model->texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model->texture.width, model->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, model->texture.data);
			glGenerateMipmap(GL_TEXTURE_2D);
			model->texture_exists = 1;
		}
		else
			ft_putstr("Failed to parsing texture\n");
	}
	else
	{
		ft_putstr("Failed to load texture\n");

	}
}

void model_bind_texture(t_model * model)
{
	if(model->texture.data)
	{
		model->shader->set_int(model->shader, "texture1", 0);
	}
}


int main(int argc, char **argv)
{
	t_gl gl;
	init_gl(SCR_HEIGHT, SCR_HEIGHT, &gl);


	t_model model;
	model.texture_exists = 0;
	load_obj(&model, argv[1]);
	model.shader = mgl_shader_create("./shaders/test.vs", "./shaders/test.fs");
	if (argc == 3)
	{
		load_texture( &model, argv[2]);
		model_bind_texture(&model);
	}
	glfwSetCursorPosCallback(gl.window, mouse_callback);

	
	glEnable(GL_DEPTH_TEST);
	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.size_vertices, model.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.size_indices, model.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
						  (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	t_mat4 proj = set_projection_matrix();
	t_mat4 view = ft_mat4_identity_matrix();
	t_camera * camera = camera_init();

	while (!glfwWindowShouldClose(gl.window))
	{
		// input
		// -----
		processInput(gl.window);
		// gui_update();
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		t_mat4 model_matrix = ft_mat4_identity_matrix();
		model_matrix = ft_mat4_multiply_mat4(ft_mat4_translation_matrix(model.center), model_matrix);
		// ft_mat4_print(model_matrix);
		// exit(1);
		model_matrix = ft_mat4_multiply_mat4(model_matrix, ft_mat4_rotation_matrix((t_vec3){0,1,0},(float)glfwGetTime() * 1.0f));
		view = ft_look_at(camera->position, ft_vec3_sum(camera->position,camera->camera_front), camera->camera_up);
		

		//  ft_bzero(wasd, sizeof(wasd));
		// ft_mat4_print(view);
		model.shader->use(model.shader);
		glBindVertexArray(VAO);
		model.shader->set_int(model.shader, "color", 0);
		model.shader->set_int(model.shader, "texture_exists", model.texture_exists);
		model.shader->set_mat4(model.shader, "model", &model_matrix);
		model.shader->set_mat4(model.shader, "view", &view);
		model.shader->set_mat4(model.shader, "projection", &proj);

		// model_matrix = mat4_mul(mat4_transpose(model_matrix),
		// mat4_mul(view, proj));
		// shader.set_mat4(&shader, "model", &model_matrix);

		// glDrawArrays(GL_TRIANGLES, 0, model.num_vertices / 3);
		glDrawElements(GL_TRIANGLES, model.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	
		// gui_render();
		glfwSwapBuffers(gl.window);
		glfwPollEvents();
	}
	// gui_terminate();
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	t_camera * camera;
	camera = camera_init();
   const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position, ft_vec3_scalar_multiply(camera->camera_front, cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position, ft_vec3_scalar_multiply(camera->camera_front, cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position,
		ft_vec3_scalar_multiply(ft_vec3_normalize(ft_vec3_cross_multiply(camera->camera_front, camera->camera_up)), cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position,
		ft_vec3_scalar_multiply(ft_vec3_normalize(ft_vec3_cross_multiply(camera->camera_front, camera->camera_up)), cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		exit(0);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position, ft_vec3_scalar_multiply(camera->camera_up, cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position, ft_vec3_scalar_multiply(camera->camera_up, cameraSpeed));
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_camera * cam;

	cam = camera_init();

	if (cam->mouse->firstMouse)
	{
		cam->mouse->lastX = xpos;
		cam->mouse->lastY = ypos;
		cam->mouse->firstMouse = 0;
	}

	float xoffset = xpos - cam->mouse->lastX;
	float yoffset = cam->mouse->lastY - ypos; 

	cam->mouse->lastX = xpos;
	cam->mouse->lastY = ypos;

	camera_process(xoffset, yoffset);
}
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
// 	camera.ProcessMouseScroll(yoffset);
// }