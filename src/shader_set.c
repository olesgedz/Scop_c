/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:10:04 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 23:11:50 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ugl.h"
#include "shader.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "libmath.h"

int		shader_use(t_shader *shader)
{
	glUseProgram(shader->shader_program);
	return (0);
}

void	mgl_shader_setint(t_shader *shader, char *name, int value)
{
	glUniform1i(glGetUniformLocation(shader->shader_program,
	name), value);
}

void	mgl_shader_setmat4(t_shader *shader, char *name, t_mat4 *mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->shader_program, name),
	1, GL_FALSE, &mat->matrix[0][0]);
}

void	mgl_set_vec3(t_shader *shader, char *name, t_vec3 *vec)
{
	glUniform3fv(glGetUniformLocation(shader->shader_program,
	name), 1, &vec->x);
}
