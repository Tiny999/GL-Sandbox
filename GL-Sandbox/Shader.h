#pragma once

#include <glad/glad.h>


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragPath);
	void Use();
	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void Set2Float(const std::string& name, float v1, float v2);

private:
	unsigned int id;
	std::string LoadShader(const std::string& path);
	void GenShader(const std::string& path, unsigned int type);
};

