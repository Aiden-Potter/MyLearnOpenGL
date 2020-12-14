#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <string>
#include <vector>
#include "learnopengl/Shader.h"
#include <glad/glad.h>
#include <glfw3.h>
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoord;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader shader);

	Mesh(std::vector<Vertex> vertices, 
		std::vector<unsigned int> indices, 
		std::vector<Texture> textures);

	~Mesh();
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

