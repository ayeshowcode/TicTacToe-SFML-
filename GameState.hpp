#pragma once
#include<SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace Ash
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);


	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		int turn;
		int gameState;
	};
}