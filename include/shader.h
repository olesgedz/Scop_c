/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:54:19 by jblack-b          #+#    #+#             */
/*   Updated: 2020/03/06 20:28:08 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
#define SHADER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
typedef struct s_shader t_shader;
struct s_shader
{
	int vertex_shader;
	int fragment_shader;
	int shader_program;
	char *vertex_shader_src;
	char *fragment_shader_src;
	size_t src_size;
	int (*use)(t_shader *shader);
};
int mgl_shader_create(t_shader *shader, char *v_srcfile, char *f_srcfile);

#endif