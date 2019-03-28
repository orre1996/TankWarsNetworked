#pragma once
class Keyboard
{
public:
	Keyboard();
	~Keyboard();
	void SetKey(SDL_Scancode p_ey, bool p_value);
	bool GetKeyDown(SDL_Scancode p_key);
	bool GetKeyDownOnce(SDL_Scancode p_key);
	void Update();
private:
	bool m_keys[SDL_NUM_SCANCODES];
	bool m_keysPrevious[SDL_NUM_SCANCODES];

	//skifta till f�rsta bitten
	//kolla om st�rre �n 1
	//0000 0010 == 0x02

};

