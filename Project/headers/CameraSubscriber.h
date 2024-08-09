#pragma once

#include "glm/vec3.hpp"

class CameraSubscriber
{
public:

	virtual void cameraPositionUpdate(glm::vec3 newPos) = 0;

};