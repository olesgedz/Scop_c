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
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

t_mouse mouse;
t_camera *camera;

float wasd[4] = {0, 0, 0, 0};
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
	ret.matrix[0] = s / ((float)SCR_WIDTH / (float)SCR_HEIGHT);
	ret.matrix[5] = s;
	ret.matrix[10] = -(far + near) / (far - near);
	ret.matrix[14] = -2 * far * near / (far - near);
	ret.matrix[11] = -1;
	return (ret);
}

int main(int argc, char **argv)
{
	t_gl gl;
	init_gl(SCR_HEIGHT, SCR_HEIGHT, &gl);

	t_shader shader;
	mgl_shader_create(&shader, "./shaders/test.vs", "./shaders/test.fs");

	t_model model;
	load_obj(&model, argv[1]);

	glfwSetCursorPosCallback(gl.window, mouse_callback);

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
	t_mat4 proj = set_projection_matrix(); //ft_mat4_projection(ft_deg_rad(90.f), 800 / 400, 0.1f, 10000.0f );//ft_mat4_projection(ft_deg_rad(45.f),(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f );
	//ft_mat4_print(set_projection_matrix());
	printf("                            \n");
	//ft_mat4_print(ft_mat4_projection(ft_deg_rad(45.f), 800 / 400, 0.1f, 100.0f));

	t_mat4 view = ft_mat4_identity_matrix();
	camera = camera_init();
	while (!glfwWindowShouldClose(gl.window))
	{
		// input
		// -----
		processInput(gl.window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		t_mat4 model_matrix = ft_mat4_identity_matrix();
		// model_matrix = mat4_rotate_axis(model_matrix, 2, (float)glfwGetTime() * 30.0f);
		view = ft_look_at((t_vec3){wasd[1], 0, wasd[0]}, (t_vec3){0, 0, 0}, (t_vec3){0, 1, 0});
		// ft_bzero(wasd, sizeof(wasd));
		ft_mat4_print(view);
		shader.use(&shader);
		glBindVertexArray(VAO);
		shader.set_int(&shader, "color", 0);
		shader.set_mat4(&shader, "model", &model_matrix);
		shader.set_mat4(&shader, "view", &view);
		shader.set_mat4(&shader, "projection", &proj);

		// model_matrix = mat4_mul(mat4_transpose(model_matrix),
		// mat4_mul(view, proj));
		// shader.set_mat4(&shader, "model", &model_matrix);

		// glDrawArrays(GL_TRIANGLES, 0, model.num_vertices / 3);
		glDrawElements(GL_TRIANGLES, model.num_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(gl.window);
		glfwPollEvents();
	}

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		wasd[0] -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		wasd[0] += 0.1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		wasd[1] -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		wasd[1] += 0.1;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{

	printf("ok\n");
	if (mouse.firstMouse)
	{
		mouse.lastX = xpos;
		mouse.lastY = ypos;
		mouse.firstMouse = 0;
	}

	float xoffset = xpos - mouse.lastX;
	float yoffset = mouse.lastY - ypos; // reversed since y-coordinates go from bottom to top

	mouse.lastX = xpos;
	mouse.lastY = ypos;
	// if (!cursor)
	// {
	// 	camera.ProcessMouseMovement(xoffset, yoffset);
	// }
}
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
// 	camera.ProcessMouseScroll(yoffset);
// }