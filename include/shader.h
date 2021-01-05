/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:54:19 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/05 23:11:07 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
#define SHADER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "libmath.h"
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
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
    void (*set_int)(t_shader *shader, char *name, int value);
    void (*set_mat4)(t_shader *shader, char *name, t_mat4 *mat);
    void (*set_vec3)(t_shader *shader, char *name, t_vec3 *vec);
};
t_shader * mgl_shader_create(char *v_srcfile, char *f_srcfile);
void mgl_shader_setint(t_shader *shader, char *name, int value);
void mgl_shader_setmat4(t_shader *shader, char *name, t_mat4 *mat);
void mgl_set_vec3(t_shader *shader, char *name, t_vec3 *vec);
int		shader_use(t_shader *shader);
#endif