/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:50:09 by olesgedz          #+#    #+#             */
/*   Updated: 2021/01/05 21:28:54 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "scop.h"
#include "mesh.h"
#include "libmath.h"
#include "camera.h"
#include "bmp.h"
#include "scene.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

void	read_header(char *filename, t_model * model)
{
	FILE	*file;

	if ((file = fopen(filename, "r")) == NULL)
		ft_terminate("bmp file opening (fopen) failed.");
	fseek(file, 18, SEEK_SET);
	fread(&model->texture.width, 4, 1, file);
	fread(&model->texture.height, 4, 1, file);
	fseek(file, 2, SEEK_CUR);
	fread(&model->texture.bpp, 2, 1, file);
	fclose(file);
	model->texture.oop = model->texture.bpp / 8;
	model->texture.sl = model->texture.width * model->texture.oop;
	model->texture.width < 0 ? model->texture.width = -model->texture.width : 0;
	model->texture.height < 0 ? model->texture.height = -model->texture.height : 0;
	model->texture.size = model->texture.sl * model->texture.height;
}

void	get_image(t_texture *texture, char *buffer, int i)
{
	int	h;
	int	j;
	int	size;

	h = 0;
	size = texture->size * 2;
	texture->data = (unsigned char*)ft_memalloc_s(sizeof(unsigned char) * size);
	int l = 0;
	while (i >= 0)
	{
		i -= texture->sl;
		j = 0;
		while (j < texture->sl)
		{
			texture->data[i + j] = (unsigned char)buffer[i + j + 2];
			texture->data[i + j + 1] = (unsigned char)buffer[i + j + 1];
			texture->data[i + j + 2] = (unsigned char)buffer[i + j];
			j += 3;
		}
		h += texture->sl;
	}
}

void	load_bmp(t_model * model, char *filename)
{
	int		fd;
	int		i;
	char	*buffer;

	read_header(filename, model);
	buffer = (char*)ft_memalloc_s(sizeof(char) * model->texture.size + 1);
	if ((fd = open(filename, O_RDWR)) == -1)
		ft_terminate("bmp file opening failed.");
	lseek(fd, 54, SEEK_SET);
	i = read(fd, buffer, model->texture.size);
	get_image(&model->texture, buffer, i);
	ft_strdel((char**)&buffer);
	close(fd);
}


t_mat4 set_projection_matrix()
{
	float s;
	float far;
	float near;
	float fov = 70.f;
	t_mat4 ret = ft_mat4_zero();
	far = 100.f;
	near = 0.1f;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	ret = ft_mat4_identity_matrix();
	ret.matrix[0][0] = s / ((float)SCR_WIDTH / (float)SCR_HEIGHT);
	ret.matrix[1][1] = s;
	ret.matrix[2][2] = -(far + near) / (far - near);
	ret.matrix[2][3] = -1;
	ret.matrix[3][2] = -2 * far * near / (far - near);
	return (ret);
}

void load_texture( t_model *model, char * filename)
{
	if (filename)
	{
		model->texture.data = parse_bmp(filename, &model->texture.width, &model->texture.height);
		if (model->texture.data)
		{
			glGenTextures(1, &model->texture.id);
  			glBindTexture(GL_TEXTURE_2D, model->texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model->texture.width, model->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, model->texture.data);
			glGenerateMipmap(GL_TEXTURE_2D);
			model->texture_exists = 1;
		}
		else
			ft_putstr("Failed to parsing texture\n");
	}
	else
	{
		ft_putstr("Failed to load texture\n");

	}
}

void model_bind_texture(t_model * model)
{
	if(model->texture.data)
	{
		model->shader->set_int(model->shader, "texture1", 0);
	}
}
void model_modes_init(t_model * model)
{
	model->grey = 0;
	model->texture_exists = 0;
	model->color = 0;
	model->texture_mode = 0;
	model->smooth = 0;
}
t_model * model_init()
{
	t_model * model;

	model = ft_memalloc_s(sizeof(t_model));
	model->texture.data = NULL;
	model->voa = -1;
	model->vbo_normals = -1;
	model->vbo_vertices = -1;
	model->temp_vertices = NULL;
	model->vertices = NULL;
	model->normals = NULL;
	model->shader = NULL;
	model_modes_init(model);
	return (model);
}
int strcmpend(char *heap, char *needle)
{
	int len1;
	int len2;
	int i;

	if (!heap || !needle)
		return (0);
	len1 = ft_strlen(heap);
	len2 = ft_strlen(needle);
	if (len1 < len2)
		return (0);
	while(0 <= len2)
	{
		if (heap[len1] != needle[len2])
		{
			return (0);
		}
		len1--;
		len2--;
	}
	return(1);
}

int check_params(int argc, char **argv)
{
	if (argc == 1)
		ft_terminate ("usage: model.obj [texture.bmp]\n");
	if (argc == 2)
	{
		if (!strcmpend(argv[1], ".obj"))
			ft_terminate("wrong model file type\n");
	}
	if (argc == 3)
	{
		if (!strcmpend(argv[2], ".bmp"))
			ft_terminate("wrong texture type\n");
	}
	return (1);
}

void upload_texture(t_model *model)
{
	glGenTextures(1, &model->texture.id);
	glBindTexture(GL_TEXTURE_2D, model->texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, model->texture.width, model->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, model->texture.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	model->texture_exists = 1;
}

void upload_model(t_model *model)
{
	glGenBuffers(1, &model->vbo_vertices);
	glGenVertexArrays(1, &model->voa);
	glBindVertexArray(model->voa);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, model->num_vertices * sizeof(float), model->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,
						  (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, model->num_normals * sizeof(float),
				model->normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}
t_scene * scene_create()
{
	static t_scene * scene = NULL;
	if (!scene)
	{
		scene = ft_memalloc_s(sizeof(t_scene));
		
	} 
	return (scene);
}
t_scene *scene_init(t_scene *scene, t_gl *gl, t_model *model)
{
	glfwSetCursorPosCallback(gl->window, mouse_callback);
	glEnable(GL_DEPTH_TEST);
	scene->light_pos = (t_vec3){0, 0, 3};
	scene->proj = set_projection_matrix();
	scene->view = ft_mat4_identity_matrix();
	scene->camera = camera_init();
	scene->model = model;
	scene->gl = gl;
	scene->last_time = 0;
	scene->last_press = 0;
	return (scene);
}
void	update_time(t_scene *scene)
{
	
	scene->current_frame = glfwGetTime();
	scene->delta = scene->current_frame - scene->last_time;
	scene->last_time = scene->current_frame;
}
void renderer(t_gl *gl, t_model *model, t_scene *scene)
{
	while (!glfwWindowShouldClose(gl->window))
	{
		
		processInput(gl->window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_time(scene);
		t_mat4 model_matrix = ft_mat4_identity_matrix();
		model_matrix = ft_mat4_multiply_mat4(ft_mat4_translation_matrix(model->center), model_matrix);
		model_matrix = ft_mat4_multiply_mat4(model_matrix, ft_mat4_rotation_matrix((t_vec3){0,1,0},(float)glfwGetTime() * 1.0f));
		scene->view = ft_look_at(scene->camera->position, ft_vec3_sum(scene->camera->position,scene->camera->camera_front), scene->camera->camera_up);
		model->shader->use(model->shader);
		glBindVertexArray(model->voa);
		model->shader->set_int(model->shader, "color", 0);
		model->shader->set_int(model->shader, "grey", model->grey);
		model->shader->set_int(model->shader, "smooth", model->smooth);
		model->shader->set_int(model->shader, "texture_mode", model->texture_mode);
		model->shader->set_mat4(model->shader, "model", &model_matrix);
		model->shader->set_mat4(model->shader, "view", &scene->view);
		model->shader->set_mat4(model->shader, "projection", &scene->proj);
		model->shader->set_vec3(model->shader, "lightPos", &scene->light_pos);
		glBindTexture(GL_TEXTURE_2D, model->texture.id);
		glDrawArrays(GL_TRIANGLES, 0, model->num_vertices);
		glBindVertexArray(0);
		glfwSwapBuffers(gl->window);
		glfwPollEvents();
	}
}
int main(int argc, char **argv)
{
	t_gl gl;
	t_model *  model;
	t_scene * scene;
	
	check_params(argc, argv);
	init_gl(SCR_HEIGHT, SCR_HEIGHT, &gl);
	model = model_init();
	load_obj(model, argv[1]);
	model->shader = mgl_shader_create("./shaders/test.vs", "./shaders/test.fs");
	if (argc == 3)
	{
		load_bmp(model, argv[2]);
		model_bind_texture(model);
		upload_texture(model);	
	}
	upload_model(model);
	scene = scene_init(scene_create(), &gl, model);
	renderer(&gl, model, scene);
	glDeleteVertexArrays(1, &model->voa);
	glDeleteBuffers(1, &model->vbo_vertices);
	glDeleteBuffers(1, &model->vbo_normals);
	glfwTerminate();
	return 0;
}

void key_switch(int *key)
{
	if (*key == 0)
		*key = 1;
	else if (*key == 1)
		*key = 0;
	else
		*key = 0;
}

void processInput(GLFWwindow *window)
{
	t_camera *camera;
	t_scene  *scene;
	camera = camera_init();
	scene = scene_create();
   const float cameraSpeed = 0.05f; 
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position, ft_vec3_scalar_multiply(camera->camera_front, cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position, ft_vec3_scalar_multiply(camera->camera_front, cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position,
		ft_vec3_scalar_multiply(ft_vec3_normalize(ft_vec3_cross_multiply(camera->camera_front, camera->camera_up)), cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position,
		ft_vec3_scalar_multiply(ft_vec3_normalize(ft_vec3_cross_multiply(camera->camera_front, camera->camera_up)), cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		exit(0);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->position = ft_vec3_sum(camera->position, ft_vec3_scalar_multiply(camera->camera_up, cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->position = ft_vec3_substract(camera->position, ft_vec3_scalar_multiply(camera->camera_up, cameraSpeed));
	if ((scene->current_frame - scene->last_press) > 0.07)
	{
		scene->last_press = scene->current_frame;
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			key_switch(&scene->model->lines);
			if (scene->model->lines == 1)
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			else
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			key_switch(&scene->model->grey);
	}
	
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_camera * cam;
	float xoffset;
	float yoffset;
	cam = camera_init();
	if (cam->mouse->firstMouse)
	{
		cam->mouse->lastX = xpos;
		cam->mouse->lastY = ypos;
		cam->mouse->firstMouse = 0;
	}
	xoffset = xpos - cam->mouse->lastX;
	yoffset = cam->mouse->lastY - ypos; 
	cam->mouse->lastX = xpos;
	cam->mouse->lastY = ypos;
	camera_process(xoffset, yoffset);
}