/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 20:50:47 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:45:24 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "libmath.h"
# include "scop.h"

typedef	struct	s_camera
{
	int			first_mouse;
	int			last_x;
	int			last_y;
	int			cursor;
	t_vec3		position;
	t_vec3		target;
	t_vec3		direction;
	t_vec3		up;
	t_vec3		camera_up;
	t_vec3		camera_right;
	t_vec3		camera_front;
	float		pitch;
	float		yaw;
	float		m_sesivity;
	t_mouse		*mouse;
}				t_camera;

t_camera *camera_init();
void camera_update();
void camera_process(float xoffset, float yoffset);
#endif