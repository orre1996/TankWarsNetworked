#pragma once
class Mouse
{
public:
	Mouse();
	~Mouse();
	bool GetButtonDown(Uint8 p_index);
	bool GetButtonPressed(Uint8 p_index);
	bool GetButtonReleased(Uint8 p_index);
	void SetButton(Uint8 p_button, bool p_value);
	SDL_Point GetPosition();
	SDL_Point GetMotion();
	void SetMotion(SDL_MouseMotionEvent p_event);
	void Update();
private:
	bool m_buttons[5];
	bool m_buttonsPrevious[5];
	SDL_Point m_position;
	SDL_Point m_motion;
};

