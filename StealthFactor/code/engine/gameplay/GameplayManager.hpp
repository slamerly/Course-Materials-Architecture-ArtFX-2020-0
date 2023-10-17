#pragma once

#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <engine/gameplay/entities/Player.hpp>
#include <engine/IManager.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;

		namespace entities
		{
			class Player;
		}

        class GameplayManager : public IManager
        {
        public:

            GameplayManager();

            void initialize() override;
            void update() override;
            void clear() override;

            void gameOver();

            sf::Vector2f getViewCenter() const;

            void loadMap(const std::string& mapName);
            void loadNextMap();

            const entities::Player& getPlayer() const;

            static const float CELL_SIZE;

        private:

            std::set<Entity*> entities;
            entities::Player* playerEntity{};

            std::string currentMapName;
            std::string nextMapName;
            int rows{ 0 };
            int columns{ 0 };

            bool preventMapCompletion{ false };
            bool nextMapRequested{ false };
        };
	}
}
