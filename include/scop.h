/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:48:38 by olesgedz          #+#    #+#             */
/*   Updated: 2021/01/05 22:29:07 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include "stb_image.h"
# include "ugl.h"
# include "shader.h"
# include "mesh.h"

# define SCR_WIDTH 800
# define SCR_HEIGHT 600

typedef struct	s_mouse
{
	int			first_mouse;
	int 		last_x;
	int			last_y;
	int			cursor;
}				t_mouse;
void			mouse_callback(GLFWwindow *window, double xpos, double ypos);
void			framebuffer_size_callback(GLFWwindow *window, int width, int height);
void			processInput(GLFWwindow *window);
#endif