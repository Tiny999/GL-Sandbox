#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "Shader.h"

struct Vertex
{
	glm::vec3 Position, Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	std::string type, path;
	unsigned int id;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<unsigned int> indices);
	void Draw(Shader& shader);

private:
	unsigned int VAO, VBO, IBO;
	void SetupMesh();
};

