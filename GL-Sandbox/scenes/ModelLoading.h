#pragma once

#include "../Model.h"
#include "../Shader.h"
#include "../Scene.h"

class ModelLoading : public Scene
{
public:
	ModelLoading() = default;
	void Load() override;
	void Render(Camera& camera, glm::mat4& projection, float delta) override;

private:
	Shader shader = Shader("shaders/modelLoading.vertex.glsl", "shaders/modelLoading.frag.glsl");
	Model backpackModel = Model("assets/models/backpack/backpack.obj");

};
