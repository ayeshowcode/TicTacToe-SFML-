#include<sstream>
#include "GameOverState.hpp"
#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

#include<iostream>

namespace Ash
{
	GameoverState::GameoverState(GameDataRef data) : _data(data)
	{

	}
	void GameoverState::init()
	{
		this->_data->assets.LoadTexture("Retry Background", RETRY_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);


		this->_retryButton.setTexture(this->_data->assets.GetTexture("Retry Background"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("Home Button"));


		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2));


		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2),
			(this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));


	}

	void GameoverState::HandleInput()
	{
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.isSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState (_data)), true);
			}
			if (this->_data->input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();

				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void GameoverState::Update(float dt)
	{

	}

	void GameoverState::Draw(float dt)
	{
		this->_data->window.clear(sf:: Color ::Red);

		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();

	}
}