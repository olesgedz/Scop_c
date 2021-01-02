/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:48:38 by olesgedz          #+#    #+#             */
/*   Updated: 2020/03/10 20:56:14 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "ugl.h"
#include "shader.h"
#include "mesh.h"

#define  SCR_WIDTH 800
#define SCR_HEIGHT  600
typedef struct s_mouse
{
    int firstMouse;
    int lastX;
    int lastY;
    int cursor;
} t_mouse;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
#endif