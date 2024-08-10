#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "CameraSubscriber.h"

class UserInputController;

class TileV2;

struct UserInfo
{
	std::optional<glm::ivec2> TilePos; // on which tile is the user
};

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

	void playerOnNewTile(UserInfo before, UserInfo after);
	void generateTiles(glm::ivec2 difference);

	glm::vec3 m_startPosition; // bottom left of whole tile set
	UserInfo m_UserInfo;

	std::vector<std::unique_ptr<TileV2>> m_Tiles;

};