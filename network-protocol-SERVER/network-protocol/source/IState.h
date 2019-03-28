#pragma once
#include <string>
#include <vector>
class IState
{
public:
	IState();
	virtual ~IState();
	virtual void SetX(int p_x);
	virtual void SetY(int p_y);
	virtual void Enter();
	virtual void Exit();
	virtual void Update(float p_delta) = 0;
	virtual void Draw() = 0;
};

