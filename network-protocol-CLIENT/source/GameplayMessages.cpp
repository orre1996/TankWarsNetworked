#include "stdafx.h"
#include "GameplayMessages.h"
//#include "TextString.h"
#include <algorithm>


GameplayMessages::GameplayMessages(int p_x, int p_y)
{
	m_x = p_x;
	m_y = p_y;
}


GameplayMessages::~GameplayMessages()
{
	for (int i = 0; i < textMessages.size(); i++)
	{
		delete textMessages[i];
		textMessages[i] = nullptr;
	}		
}

void GameplayMessages::AddTextMessage(std::string p_string, float timerLength, int textOffset)
{
	bool messageExists = false;
	for (int i = 0; i < textMessages.size(); i++)
	{
		if (textMessages[i]->textString->GetText() == p_string)
			messageExists = true;
	}

	if (!messageExists)
	{
		for (int i = 0; i < textMessages.size(); i++)
		{
			textMessages[i]->textString->SetPosition(textMessages[i]->textString->GetX(), textMessages[i]->textString->GetY() + textOffset);
		}

		TextMessage* textMessage = new TextMessage(timerLength);
		textMessages.push_back(textMessage);
		textMessage->textString->SetText(p_string);
		textMessage->textString->SetPosition(m_x, m_y);
		textMessage->textString->GenerateText(p_string, m_x, m_y);
	}
}

void GameplayMessages::Draw()
{
	for (int i = 0; i < textMessages.size(); i++)
	{
		textMessages[i]->textString->DrawText();
	}
}

void GameplayMessages::Update(float p_delta)
{
	UpdateTimers(p_delta);
	for (int i = 0; i < textMessages.size(); i++)
	{
		TextString* textString = textMessages[i]->textString;
		textString->GenerateText();
	}
}

void GameplayMessages::UpdateTimers(float p_delta)
{
	for (int i = 0; i < textMessages.size(); i++)
	{

		if (textMessages[i]->timerCurrent < textMessages[i]->timerMax)
		{
			textMessages[i]->timerCurrent += p_delta;

		}
	}

	for (int i = 0; i < textMessages.size(); i++)
	{
		if (textMessages[i]->timerCurrent >= textMessages[i]->timerMax)
		{
			delete textMessages[i];
			textMessages[i] = nullptr;
		}
	}
	textMessages.erase(std::remove(textMessages.begin(), textMessages.end(), nullptr), textMessages.end());

}

