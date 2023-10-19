#pragma once

namespace engine
{
    namespace graphics
    {
        class GraphicsManager;
    }

    namespace input
    {
        class InputManager;
    }

    namespace physics
    {
        class PhysicsManager;
    }

    namespace gameplay
    {
        class EntityListener;

        struct EntityContext
        {
            graphics::GraphicsManager& graphicsManager;
            input::InputManager& inputManager;
            physics::PhysicsManager& physicsManager;
            EntityListener& entityListener;
        };
    }
}