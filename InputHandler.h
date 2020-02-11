#pragma once

class Player;

class InputHandler
{
public:
	InputHandler(Player* owner);
	~InputHandler();

	void handleInput();

private:

	Player* m_owner;
	bool bIsPressingKey;

};

