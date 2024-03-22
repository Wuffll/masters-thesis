#pragma once

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>

#define STRING(value) (std::to_string(value))
#define GLM_TOSTRING(value) (glm::to_string(value))

class Util
{
public:

private:

};