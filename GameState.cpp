//GameState.cpp
#include<sstream>
#include "GameState.hpp"
#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

#include<iostream>

namespace Ash
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}
	void GameState::init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));


		_pauseButton.setPosition(this->_data->window.getSize().x -_pauseButton.getLocalBounds().width,
			_pauseButton.getPosition().y); 
		_gridSprite.setPosition(SCREEN_WIDTH / 2 - (_gridSprite.getGlobalBounds().width / 2),
			SCREEN_HEIGHT / 2 - (_gridSprite.getGlobalBounds().height / 2));
		

		initGridPieces();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				gridArray[i][j] = EMPTY_PIECE;
			}
		}
	}


	void GameState::HandleInput()
	{
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
			{
				this->checkAndPlacePiece();
			}
		}
	}

	void GameState::Update(float dt)
	{

	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color :: Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->_data->window.draw(this->_gridPieces[i][j]);
			}
		}


		this->_data->window.display();
	}
	void GameState::initGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_gridPieces[i][j].setTexture(this->_data->assets.GetTexture("X Piece"));

				_gridPieces[i][j].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * i) - 7,
					_gridSprite.getPosition().y + (tempSpriteSize.y * j) - 7);

				_gridPieces[i][j].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState:: checkAndPlacePiece()
	{
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width )/ 2, (SCREEN_HEIGHT - gridSize.height )/ 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int col, row;
		// check which column the user has clicked 
		if (gridLocalTouchPos.x < gridSectionSize.x) // first column
		{
			col = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2) // second column
		{
			col = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width) // third column
		{
			col = 3;
		}
		 
		// check which row the user has clicked 
		if (gridLocalTouchPos.y < gridSectionSize.y) // first row 
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2) // second row 
		{
			row = 2;
		} 
		else if (gridLocalTouchPos.y < gridSize.height) // third row 
		{
			row = 3;
		}

		if (gridArray[col - 1][row - 1] == EMPTY_PIECE)
		{
			gridArray[col - 1][row - 1] = turn;
			if (PLAYER_PIECE == turn)
			{
			_gridPieces[col - 1][row - 1].setTexture(this->_data->assets.GetTexture("X Piece"));
			turn = AI_PIECE;
			}
			else if (AI_PIECE == turn)
			{
				_gridPieces[col - 1][row - 1].setTexture(this->_data->assets.GetTexture("O Piece"));
				turn = PLAYER_PIECE;
			}
			_gridPieces[col - 1][row - 1].setColor(sf:: Color(255, 255, 255, 255));
		}
	}
}