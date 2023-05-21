#pragma once
struct obstacle
{
	char name[20];
	float pos_x;
	float pos_y;
	float v_x;
	int width;
	int height;
	bool enable = 0;
};
