#pragma once

#include <glad/glad.h>

#include "Camera.h"

class Scene
{
public:
	virtual void Load() = 0;
	virtual void Render(Camera& camera, glm::mat4& projection) = 0;
};

