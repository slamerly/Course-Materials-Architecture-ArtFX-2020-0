#pragma once

#include <engine/graphics/ShapeList.hpp>

namespace engine
{
    namespace graphics
    {
        struct ShapeListInstance;

        struct ShapeListInstance
        {
            ShapeList shapeList;
            sf::Transform transform;
        };

        using ShapeListId = ShapeListInstance*;
    }
}