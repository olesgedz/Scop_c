/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:53:18 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 23:29:45 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ugl.h"
#include "shader.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "libmath.h"

void		mgl_shader_compile(t_shader *shader, int *success, char *info_log)
{
	shader->shader_program = glCreateProgram();
	glAttachShader(shader->shader_program, shader->vertex_shader);
	glAttachShader(shader->shader_program, shader->fragment_shader);
	glLinkProgram(shader->shader_program);
	glGetProgramiv(shader->shader_program, GL_LINK_STATUS, success);
	if (!success)
	{
		glGetProgramInfoLog(shader->shader_program, 512, NULL, info_log);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s\n", info_log);
	}
	glDeleteShader(shader->vertex_shader);
	glDeleteShader(shader->fragment_shader);
	shader->use = shader_use;
	shader->set_int = mgl_shader_setint;
	shader->set_mat4 = mgl_shader_setmat4;
	shader->set_vec3 = mgl_set_vec3;
}

void		mgl_shader_compile_f(t_shader *shader, int *success, char *info_log)
{
	glShaderSource(shader->fragment_shader, 1,
	(const char *const *)&shader->fragment_shader_src, NULL);
	glCompileShader(shader->fragment_shader);
	glGetShaderiv(shader->fragment_shader, GL_COMPILE_STATUS, success);
	if (!success)
	{
		glGetShaderInfoLog(shader->fragment_shader, 512, NULL, info_log);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n ", info_log);
	}
}

t_shader	*mgl_shader_create(char *v_srcfile, char *f_srcfile)
{
	t_shader	*shader;
	int			success;
	char		info_log[512];

	shader = ft_memalloc_s(sizeof(t_shader));
	shader->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	shader->vertex_shader_src = readfile(v_srcfile);
	glShaderSource(shader->vertex_shader, 1,
	(const char *const *)&shader->vertex_shader_src, NULL);
	glCompileShader(shader->vertex_shader);
	glGetShaderiv(shader->vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader->vertex_shader, 512, NULL, info_log);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n ", info_log);
	}
	shader->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	shader->fragment_shader_src = readfile(f_srcfile);
	mgl_shader_compile_f(shader, &success, info_log);
	mgl_shader_compile(shader, &success, info_log);
	return (shader);
}
