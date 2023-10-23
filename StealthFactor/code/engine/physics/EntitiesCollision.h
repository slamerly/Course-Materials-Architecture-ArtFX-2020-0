#pragma once
#include <functional>
#include <vector>
#include <engine/gameplay/Entity.hpp>

namespace engine
{
	namespace physics
	{
		using EntitySet = std::vector<const gameplay::Entity*>;
	}
}
