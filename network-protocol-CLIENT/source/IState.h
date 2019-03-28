#pragma once
#include "types.h"

class IState
{
public:
	IState();
	virtual ~IState();

	virtual void Update(uint8_t p_delta) = 0;
	virtual void Draw() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};
