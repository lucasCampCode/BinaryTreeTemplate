#include "TreeNode.h"
#include <iostream>
#include "raylib.h"

TreeNode::TreeNode(int value)
{
	//puts the value into the node
	m_value = value;
}

void TreeNode::draw(int x, int y, bool selected)
{
	//holds a string value for the value inside the node
	static char buffer[10];
	//converts an int to string
	sprintf(buffer, "%d", m_value);
	//draws the outer circle
	DrawCircle(x, y, 30, YELLOW);
	//draws the inner circle based on if sellected
	if (selected)
		DrawCircle(x, y, 28, GREEN);
	else
		DrawCircle(x, y, 28, BLACK);

	//draws the value inside the circle
	DrawText(buffer, x - 12, y - 12, 12, WHITE);
}