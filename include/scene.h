/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:16:48 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 22:34:59 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "libmath.h"
#include "camera.h"

typedef struct	    s_scene
{
	t_vec3          light_pos;
    t_mat4          proj;
    t_mat4          view;
    t_mat4          model_matrix;
    t_camera        *camera;
    t_model         *model;
    t_gl            *gl;
    float    delta;
    float    last_time;
    float    last_press;
    float    current_frame;
}				    t_scene;
#endif