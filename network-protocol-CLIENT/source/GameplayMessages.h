#pragma once
#include <string>
#include <vector>
#include "protocol.h"

#include "TextString.h"


struct TextMessage
{
	TextString* textString;
	float timerMax;
	float timerCurrent;

public:
	TextMessage(float p_timerLength)
	{
		textString = new TextString();
		timerMax = p_timerLength;
		timerCurrent = 0.0f;
	}
	~TextMessage()
	{
		delete textString;
		textString = nullptr;
	}
};

class GameplayMessages
{
public:
	GameplayMessages(int p_x, int p_y);
	~GameplayMessages();
	void Draw();
	void Update(float p_delta);
	void AddTextMessage(std::string p_string, float timerLength, int textOffset);
	void UpdateTimers(float p_delta);

	private:
		int m_x;
		int m_y;
	int time;
	std::vector<TextMessage*> textMessages;
	std::vector<int> playerScores;
};

