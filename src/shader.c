/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:53:18 by jblack-b          #+#    #+#             */
/*   Updated: 2020/03/10 21:13:08 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ugl.h"
#include "shader.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "libmath.h"

char *vertexShaderSource = "#version 330 core\n"
						   "layout (location = 0) in vec3 aPos;\n"
						   "void main()\n"
						   "{\n"
						   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
						   "}\0";
char *fragmentShaderSource = "#version 330 core\n"
							 "out vec4 FragColor;\n"
							 "void main()\n"
							 "{\n"
							 "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
							 "}\n\0";

int shader_use(t_shader *shader)
{
	glUseProgram(shader->shader_program);
	return 0;
}

int mgl_shader_create(t_shader *shader, char *v_srcfile, char *f_srcfile)
{
	shader->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	shader->vertex_shader_src = readfile(v_srcfile);
	glShaderSource(shader->vertex_shader, 1, (const char *const *)&shader->vertex_shader_src, NULL);
	glCompileShader(shader->vertex_shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader->vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader->vertex_shader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n ", infoLog);
	}
	// fragment shader
	shader->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	shader->fragment_shader_src = readfile(f_srcfile);
	glShaderSource(shader->fragment_shader, 1, (const char *const *)&shader->fragment_shader_src, NULL);
	glCompileShader(shader->fragment_shader);
	// check for shader compile errors
	glGetShaderiv(shader->fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader->fragment_shader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n ", infoLog);
	}
	// link shaders
	shader->shader_program = glCreateProgram();
	glAttachShader(shader->shader_program, shader->vertex_shader);
	glAttachShader(shader->shader_program, shader->fragment_shader);
	glLinkProgram(shader->shader_program);
	// check for linking errors
	glGetProgramiv(shader->shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->shader_program, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s\n", infoLog);
	}
	glDeleteShader(shader->vertex_shader);
	glDeleteShader(shader->fragment_shader);
	shader->use = shader_use;
	shader->set_int = mgl_shader_setInt;
	shader->set_mat4 = mgl_shader_setMat4;
	return 0;
}
void mgl_shader_setInt(t_shader *shader, char *name, int value)
{
	glUniform1i(glGetUniformLocation(shader->shader_program, name), value);
}
void mgl_shader_setMat4(t_shader *shader, char *name, t_mat4 *mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->shader_program, name), 1, GL_FALSE, &mat->matrix[0]);
}