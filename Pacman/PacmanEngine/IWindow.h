#pragma once

class IWindow
{
public:
	//TODO: GetEvents when Events are implemented
	//virtual void GetEvents() = 0;
	virtual void DrawLine() = 0;
	virtual void DrawText(uint16_t score) = 0;
	virtual void DrawTexture() = 0;
};