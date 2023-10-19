#pragma once

#include <engine/graphics/ShapeListObserver.h>
#include <engine/gameplay/Entity.hpp>
#include <engine/physics/CollisionVolumeId.h>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            class Character : public Entity
            {
            public:
                Character(EntityContext& context);
                virtual ~Character();

                void propagateTransform();

            protected:
                graphics::ShapeListId _shapeListId;
                physics::CollisionVolumeId _collisionVolumeId;

                bool _isWalking{ false };
            };
        }
    }
}