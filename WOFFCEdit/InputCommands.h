#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;

	bool rotRight;
	bool rotLeft;

	bool moveCamera;
	bool Up;
	bool Down;
	bool mouseUp;
	bool mouseDown;

	int mouseX, mouseY;
	bool mouseOriginX, mouseOriginY;
	bool windowMouseX, windowMouseY;

	//bool mouseLUP;
	bool mouseLDown;
	bool mouseRDown;
};
