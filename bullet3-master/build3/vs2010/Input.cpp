#include "Input.h"

Input::Input()
{
	//m_uiElements = {};
	m_command = Command::CM_INVALID;
}
Input::~Input()
{
	//m_uiElements.clear();
	character = nullptr;
}

void Input::keyboardUp(unsigned char key, int x, int y)
{
	std::cout << "Key released: " << key << std::endl;

	auto* playerMov = dynamic_cast<PlayerMovement*>(character->GetMovement());

	switch (key) {
	case 'd':
	case 'a':
	case 'w':
	case 's':
		playerMov->SetCurrentDirection(btVector3(0, 0, 0));
		break;
	default:
		break;
	}
}

void Input::keyboard(unsigned char key, int x, int y) 
{
	auto* playerMov = dynamic_cast<PlayerMovement*>(character->GetMovement());

	switch (key) {
	case 'd':
		playerMov->SetCurrentDirection(btVector3(1, 0, 0));
		break;
	case 'a':
		playerMov->SetCurrentDirection(btVector3(-1, 0, 0));
		break;
	case 'w':
		playerMov->SetCurrentDirection(btVector3(0, 0, 1));
		break;
	case 's':
		playerMov->SetCurrentDirection(btVector3(0, 0, -1));
		break;
	default:
		playerMov->SetCurrentDirection(btVector3(0, 0, 0));
		break;
	}

}
//void Input::UpdateUIElements(int currentState)
//{
//	for (auto& uiElement : m_uiElements)
//	{
//		if ((int)uiElement.gameState == currentState)
//		{
//			uiElement.sprite->IsActive(true);
//			uiElement.sprite->IsVisible(true);
//		}
//		else
//		{
//			uiElement.sprite->IsActive(false);
//			uiElement.sprite->IsVisible(false);
//		}
//	}
//}

//void Input::mouse(int button, int state, int x, int y)
//{
//	m_command = Command::CM_STOP;
//
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//	{
//		for (unsigned int i = 0; i < m_uiElements.size(); i++)
//		{
//			Sprite* element = m_uiElements[i].sprite;
//			if (element->CheckIfActive())
//			{
//				if (CheckForClick(element, x, y))
//				{
//					element->IsClicked(true);
//					m_command = Input::Command::CM_UI;
//					return;
//				}
//			}
//		}
//
//		m_command = Command::CM_UP;
//	}
//	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//	{
//		m_command = Command::CM_DOWN;
//	}
//	else
//	{
//		m_command = Command::CM_INVALID;
//	}
//}
//
//void Input::AddUiElement(Sprite* p_element, int gameState)
//{
//	m_uiElements.emplace_back(p_element, gameState);
//}

void Input::AddCharacter(GameObject& character_)
{
	character = &character_;
}
//const bool Input::CheckForClick(Sprite* p_element, int x, int y) const
//{
//	float left = p_element->GetPosX();
//	float right = p_element->GetPosX() + p_element->GetWidth();
//
//	float top = p_element->GetPosY();
//	float bottom = p_element->GetPosY() + p_element->GetHeight();
//
//	if (x >= left && x <= right &&  y >= top && y <= bottom) return true;
//	else                                           	         return false;
//}