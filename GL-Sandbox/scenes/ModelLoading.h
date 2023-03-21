#pragma once

#include "../Model.h"
#include "../Shader.h"
#include "../Scene.h"

class ModelLoading : public Scene
{
public:
	ModelLoading() = default;
	ModelLoading(std::string vs_path, std::string frag_path, std::string model_path);
	void Load() override;
	void Render(Camera& camera, glm::mat4& projection, float delta) override;

private:
	Shader shader;
	Model model;

	std::string& vs_path, fs_path, model_path;
};
