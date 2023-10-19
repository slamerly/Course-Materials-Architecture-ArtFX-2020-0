#include "Character.hpp"

#include <cassert>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            Character::Character(EntityContext& context)
                : Entity{ context }
            {
                _collisionVolumeId = context.physicsManager.createCollisionBox(this, gameplay::GameplayManager::CELL_SIZE * 0.9f, gameplay::GameplayManager::CELL_SIZE * 0.9f);
                assert(_collisionVolumeId);
            }

            Character::~Character()
            {
                context.graphicsManager.destroyShapeListInstance(_shapeListId);
                context.physicsManager.destroyCollisionVolume(_collisionVolumeId);
            }

            void Character::propagateTransform()
            {
                context.graphicsManager.setShapeListInstanceTransform(_shapeListId, getTransform());
                context.physicsManager.setCollisionVolumePosition(_collisionVolumeId, getPosition());
            }
        }
    }
}