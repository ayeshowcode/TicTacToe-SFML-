//State.hpp
#pragma once
namespace Ash
{
	class State
	{
	public:
		virtual void init() = 0;

		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(float dt) = 0;

		virtual void Pause() {}
		virtual void Resume() {}

	};

}