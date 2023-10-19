#include <engine/physics/CollisionVolumeId.h>
#include <engine/graphics/ShapeListObserver.h>
#include "Target.hpp"

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
            Target::Target(EntityContext& context)
                : Entity{ context }
            {
                shapeListId = context.graphicsManager.createShapeListInstance("target");
                assert(shapeListId);

                collisionVolumeId = context.physicsManager.createCollisionBox(this, gameplay::GameplayManager::CELL_SIZE * 0.9f, gameplay::GameplayManager::CELL_SIZE * 0.9f);
                assert(collisionVolumeId);
            }

            Target::~Target()
            {
                context.graphicsManager.destroyShapeListInstance(shapeListId);
                context.physicsManager.destroyCollisionVolume(collisionVolumeId);
            }

            void Target::update()
            {
                propagateTransform();
            }

            void Target::propagateTransform()
            {
                context.graphicsManager.setShapeListInstanceTransform(shapeListId, getTransform());

                auto& position = getPosition();
                dGeomSetPosition(collisionVolumeId, position.x, position.y, 0);
            }
        }
    }
}