#pragma once
#include "GameObject.h"
#include "PlayerMovement.h"

class Input
{
public:
	enum Command
	{
		CM_INVALID = -1,
		CM_STOP,
		CM_UP,
		CM_DOWN,
		CM_QUIT,
		CM_UI
	}; 
	/*struct UIElement
	{
		Sprite* sprite;
		int gameState;

		UIElement(Sprite* sprite, int gameState)
			: sprite(sprite), gameState(gameState) {}
	};*/
protected:
	Command m_command;
	//std::vector<UIElement> m_uiElements;
	GameObject* character;

	//const bool CheckForClick(Sprite* p_element, int x, int y) const;
public:
	Input();
	~Input();
	
	const Command GetCommand() const { return m_command; }
	void SetCommand(Command command) { m_command = command; }
	void mouse(int button, int state, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
	void keyboard(unsigned char key, int x, int y);

	//void AddUiElement(Sprite* p_element, int gameState);
	void AddCharacter(GameObject& character_);
	void UpdateUIElements(int currentState);
};