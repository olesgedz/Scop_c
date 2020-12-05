/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:50:47 by jblack-b          #+#    #+#             */
/*   Updated: 2020/03/10 20:52:23 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
#define CAMERA_H
#include "libmath.h"
typedef struct s_camera
{
	int firstMouse;
	int lastX;
	int lastY;
	int cursor;
	t_vec3 position;
	t_vec3 target;
	t_vec3 direction;
	t_vec3 up;
	t_vec3 camera_up;
	t_vec3 camera_right;
	t_vec3 camera_front;
} t_camera;

t_camera *camera_init();
#endif