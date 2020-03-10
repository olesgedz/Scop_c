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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

t_mouse mouse;



int main(int argc , char ** argv)
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
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

	while (!glfwWindowShouldClose(gl.window))
	{
		// input
		// -----
		processInput(gl.window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use(&shader);
		glBindVertexArray(VAO);
		shader.set_int(&shader, "color", 0);
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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

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