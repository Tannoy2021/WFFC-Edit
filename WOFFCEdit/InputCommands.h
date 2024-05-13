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

	bool manipulationRotation;

	bool enableManipulation;
	bool manipulationUp;
	bool manipulationDown;
	bool manipulationLeft;
	bool manipulationRight;
	bool manipulationScaleUp;
	bool manipulationScaleDown;
	bool manipulationMoveObject;

	bool generateObject;

	bool deleteObject;
	bool gotoObject;

	
};
