/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:47:24 by jblack-b          #+#    #+#             */
/*   Updated: 2021/01/06 15:50:50 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H
# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include "stb_image.h"
# include "shader.h"

typedef struct			s_texture
{
	unsigned int		id;
	int					width;
	int					height;
	int					nr_channels;
	short				bpp;
	short				oop;
	int					sl;
	int					size;
	unsigned char		*data;
}						t_texture;

typedef struct			s_model
{
	GLuint				voa;
	GLuint				vbo_vertices;
	GLuint				vbo_normals;
	GLfloat				*vertices;
	GLfloat				*normals;
	GLuint				*indices;
	GLfloat				*temp_vertices;
	unsigned int		r_size_vertices;
	unsigned int		size_indices;
	unsigned int		size_vertices;
	unsigned int		num_indices;
	unsigned int		num_vertices;
	unsigned int		num_normals;
	t_texture			texture;
	float				velocity;
	char				*filename;
	int					texture_exists;
	int					color;
	int					grey;
	int					smooth;
	int					texture_mode;
	int					normal;
	int					light;
	int					lines;
	t_vec3				center;
	t_shader			*shader;

}						t_model;
void					load_obj(t_model *model, char *filename);
int						array_len(void **tab);
GLuint					*array_copy(GLuint *array, int length, int m);
GLfloat					*add_vertices(GLfloat *array, char *line, int *length);
GLuint					*add_indices(GLuint *array, char *line, int *length);
t_vec3					center_axis(GLfloat *vertices, int num_vertices);
#endif
