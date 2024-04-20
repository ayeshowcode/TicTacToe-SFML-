#pragma once
#include<SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace Ash
{
	class GameoverState : public State
	{
	public:
		GameoverState(GameDataRef data);

		void init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);


	private:
		GameDataRef _data;

		sf::Sprite _retryButton;

		sf::Sprite _homeButton;

	};
}