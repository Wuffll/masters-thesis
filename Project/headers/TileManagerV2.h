#pragma once

#include <vector>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "CameraSubscriber.h"

class UserInputController;

class TileV2;

class TileManagerV2 : public CameraSubscriber
{
public:

	TileManagerV2();
	TileManagerV2(glm::vec3 startPos);
	TileManagerV2(glm::vec3 startPos, glm::ivec2 tileSize);

	void draw();

	glm::vec3 getCenter() const;

	virtual void cameraPositionUpdate(glm::vec3 newPos);

private:

	glm::vec3 m_startPosition; // bottom left of whole tile set

	std::vector<std::unique_ptr<TileV2>> m_Tiles;

};