#pragma once

#include <glm/vec3.hpp>

class UserPositionSubscriber
{
public:

	virtual void userPositionUpdate(const glm::vec3& position) = 0;

};