/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ugl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:45:56 by jblack-b          #+#    #+#             */
/*   Updated: 2020/03/06 18:25:15 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UGL_H
#define UGL_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
typedef struct s_gl
{
	GLFWwindow* window;
}				t_gl;
int init_gl();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif