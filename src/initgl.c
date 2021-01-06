/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:43:29 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 14:23:04 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		init_gl(int w_h, int w_w, t_gl *gl)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	gl->window = glfwCreateWindow(w_w, w_h, "Scop", NULL, NULL);
	if (gl->window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(gl->window);
	glfwSetFramebufferSizeCallback(gl->window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return (-1);
	}
	return (0);
}

void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}
