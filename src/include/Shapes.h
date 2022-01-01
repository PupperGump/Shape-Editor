#pragma once
#include <Core.h>
#include <Window.h>

class Shape
{
public:
	sf::Vector2f position;
	sf::Color color;
	Win* win;
	bool dragging = 0;
	float offsetx{}, offsety{};

	// implicit through inheritance, set to useless by default
	Shape()
	{
		position = { 0,0 };
		color = sf::Color::White;
		this->win = NULL;
	}

	virtual void update()
	{
	}

	virtual void draw()
	{
	}

	virtual void highlight(sf::Color color)
	{
	}

	virtual void unhighlight()
	{
	}
};

class Rect : public Shape
{

public:
	sf::Vector2f size{};
	sf::RectangleShape rect{};

	Rect()
	{
		this->size = { 100, 100 };
		this->position = { 0,0 };
		this->win = NULL;
	}
	Rect(Win& win, sf::Vector2f position = { 0,0 }, sf::Vector2f size = { 100,100 }, sf::Color color = sf::Color::White)
	{
		this->win = &win;
		this->position = position;
		this->size = size;
		this->color = color;

		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(color);

		win.zlist.emplace_back(this);
		win.zindex++;
	}

	bool mouseover();

	void mousecenter();

	void mousedrag();

	void update();

	void highlight(sf::Color color);
	
	void unhighlight();

	void draw();

	//Rect operator=(const Rect& other)
	//{
	//	
	//	//this->win = other.win;
	//	//std::cout << this->win << ", " << other.win;
	//	this->position = other.position;
	//	this->size = other.size;
	//	this->color = other.color;
	//	std::cout << this->position.x << ", " << other.position.x;

	//	return *this;
	//}
};

class Circle : public Shape
{

public:
	sf::Vector2f size{};
	sf::CircleShape circle{};
	float radius = 100;

	Circle()
	{
		this->size = { 100, 100 };
		this->position = { 0,0 };
		this->win = NULL;
	}
	Circle(Win& win, sf::Vector2f position = { 0,0 }, float radius = 200, sf::Color color = sf::Color::White)
	{
		this->win = &win;
		this->position = position;
		this->size = size;
		this->color = color;
		this->radius = radius;

		
		circle.setPointCount(400);
		circle.setPosition(position);
		circle.setRadius(radius);
		circle.setFillColor(color);
		circle.setOrigin({ radius, radius });

		win.zlist.emplace_back(this);
		win.zindex++;
	}

	bool mouseover();

	void mousecenter();

	void mousedrag();

	void update();

	void highlight(sf::Color color);

	void unhighlight();

	void draw();

};

void zorder(Win& win);

void zdraw(Win& win);