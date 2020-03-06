#ifndef MESH_H
#define MESH_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

typedef struct	s_model
{
	// t_mat4			translation;
	// t_mat4			rotation;
	GLfloat			*vertices;
	GLuint			*indices;
	unsigned int	size_indices;
	unsigned int	size_vertices;
	unsigned int	num_indices;
	unsigned int	num_vertices;

	// t_vec3			center_axis;
	// t_vec3			inertia;
	// t_texture		texture;
	float			velocity;
	char			*filename;
}				t_model;
void	load_obj(t_model *model, char *filename);

#endif