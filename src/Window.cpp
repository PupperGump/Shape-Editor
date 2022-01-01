#pragma once
#include <Window.h>


void Win::mouseposition()
{
	mouseposi = sf::Mouse::getPosition(*window);
	mousepos = window->mapPixelToCoords(mouseposi);

	// temp: to stop shapes from running away
	if (mousepos.x < 0)
		mousepos.x = 0;
	if (mousepos.y < 0)
		mousepos.y = 0;
	if (mousepos.x > 1920)
		mousepos.x = 1920;
	if (mousepos.y > 1080)
		mousepos.y = 1080;
	//mousepos = sf::Vector2f( mouseposi.x, mouseposi.y );
}

void Win::maximize()
{
	ShowWindow(hwnd, SW_MAXIMIZE);
}

void Win::minimize()
{
	ShowWindow(hwnd, SW_MINIMIZE);
}