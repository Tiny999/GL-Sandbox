#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Text> textures, std::vector<unsigned int> indices)
	:
	vertices(vertices),
	indices(indices),
	textures(textures)
{
	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		// Set Textures

		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);


		shader.SetInt(name + number, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);

		// Draw Mesh

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Assign Attributes

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)); // Normal
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)); // TexCoords
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}
