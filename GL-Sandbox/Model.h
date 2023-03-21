#pragma once

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "stb_image.h"

#include "Mesh.h"

#include <iostream>

class Model
{
public:
	Model(const char* path);
	void Draw(Shader& shader);

private: 
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Text> textures_loaded;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Text> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
};