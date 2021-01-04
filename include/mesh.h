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
	short bpp;
	short oop;
	int sl;
	int size;
	unsigned char * data;
}  t_texture;


typedef struct	s_model
{
	// t_mat4			translation;
	// t_mat4			rotation;
	GLuint 			voa;
	GLuint			vbo_vertices;
	GLuint			vbo_normals;
	GLfloat			*vertices;
	GLfloat			*normals;
	GLuint			*indices;
	GLfloat			*temp_vertices;
	unsigned int	r_size_vertices;

	unsigned int	size_indices;
	unsigned int	size_vertices;

	unsigned int	num_indices;
	unsigned int	num_vertices;
	unsigned int	num_normals;


	// t_vec3			center_axis;
	// t_vec3			inertia;
	t_texture		texture;
	float			velocity;
	char			*filename;
	int				texture_exists;
	int 			color;
	int				grey;
	int 			lines;
	int				smooth;
	int 			texture_mode;
	t_vec3 			center;
	t_shader 		*shader;

}				t_model;
void	load_obj(t_model *model, char *filename);

#endif