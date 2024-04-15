//SplashState.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Ash
{
	class SplashState: public State
	{
	public:
		SplashState(GameDataRef data);
		void init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;

	};
}