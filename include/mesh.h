#ifndef MESH_H
#define MESH_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "shader.h"
typedef struct s_texture
{
	unsigned int  id;
	int width;
	int height;
	int nr_channels;
	unsigned char * data;
}  t_texture;


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
	t_texture		texture;
	float			velocity;
	char			*filename;
	int				texture_exists;
	int 			color;
	int				grey;
	int 			lines;
	int 			texture_mode;
	t_shader 		*shader;

}				t_model;
void	load_obj(t_model *model, char *filename);

#endif