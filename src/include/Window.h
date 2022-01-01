#pragma once
#include <Core.h>
#include <Windows.h> // All windows-based functions should be done here.

class Shape;

class Win
{
public:
	HWND hwnd = NULL;
	sf::RenderWindow* window = NULL;
	sf::View defaultview{};
	sf::Vector2i mouseposi{};
	sf::Vector2f mousepos{};
	std::vector<Shape*> zlist{};
	int zindex = 0;
	bool clicked = 0;
	bool dragging = 0;
	//bool ordered = 0;
	bool fullscreen = 0;

	sf::Vector2u lastsize{};
	sf::Vector2i lastposition{};

	Win()
	{
		std::cout << "Supply Win with a sf::RenderWindow\n";
	}
	Win(sf::RenderWindow& window)
	{
		this->window = &window;
		this->hwnd = window.getSystemHandle();
	}

	void mouseposition();

	void maximize();
	
	void minimize();
};