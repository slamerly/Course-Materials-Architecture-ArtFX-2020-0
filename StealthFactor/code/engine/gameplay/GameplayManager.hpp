#pragma once

#include <memory>
#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <engine/graphics/ViewProvider.h>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.h>
#include <engine/gameplay/EntityListener.h>

namespace engine
{
    namespace gameplay
    {
        namespace entities
        {
            class Player;
        }

        class GameplayManager : public graphics::ViewProvider, public EntityListener
        {
        public:
            GameplayManager(graphics::GraphicsManager& graphicsManager, input::InputManager& inputManager, physics::PhysicsManager& physicsManager);

            void setUp();
            void clear();

            void update();

            void loadMap(const std::string& mapName);

            // EntityListener
            void gameOver() override;
            void loadNextMap() override;
            const entities::Player& getPlayer() const override;

            // ViewProvider
            sf::Vector2f getViewCenter() const override;

            static const float CELL_SIZE;

        private:
            using EntityPtr = std::unique_ptr<Entity>;

            EntityContext _context;

            std::set<EntityPtr> _entities;
            entities::Player* _playerEntity{};

            // Map
            std::string _currentMapName;
            std::string _nextMapName;
            int _rows{ 0 };
            int _columns{ 0 };

            bool _preventMapCompletion{ false };
            bool _nextMapRequested{ false };

            void removeEntities();
        };
    }
}