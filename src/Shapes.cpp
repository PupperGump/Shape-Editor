#include <Shapes.h>



bool Rect::mouseover()
{
	if (win->mousepos.x > this->position.x && win->mousepos.y > this->position.y && win->mousepos.x < this->position.x + this->size.x && win->mousepos.y < this->position.y + this->size.y)
	{
		return 1;
	}
	else
		return 0;
}

void Rect::mousecenter()
{
	this->position.x = win->mousepos.x - this->size.x / 2;
	this->position.y = win->mousepos.y - this->size.y / 2;
}

void Rect::mousedrag()
{
	if (!dragging)
	{
		offsetx = win->mousepos.x - position.x;
		offsety = win->mousepos.y - position.y;
	}
	position.x = win->mousepos.x - offsetx;
	position.y = win->mousepos.y - offsety;
}

void Rect::update()
{
	if (win->clicked && !win->dragging)
	{
		if (mouseover())
		{
			dragging = 1;
			win->dragging = 1;
		}
	}
	else if (!win->clicked)
	{
		win->dragging = 0;
		dragging = 0;
	}


	mousedrag();

	rect.setPosition(position);
}

void Rect::highlight(sf::Color color)
{
	rect.setOutlineThickness(3);
	rect.setOutlineColor(color);
}

void Rect::unhighlight()
{
	rect.setOutlineThickness(0);
	rect.setOutlineColor(color); // just in case
}

void Rect::draw()
{
	win->window->draw(rect);
}

bool Circle::mouseover()
{
	float diffx = position.x - win->mousepos.x;
	float diffy = position.y - win->mousepos.y;

	float distance = diffx * diffx + diffy * diffy;

	if (distance < radius * radius)
	{
		return 1;
	}
	else
		return 0;
}

void Circle::mousecenter()
{
	if (dragging)
	{
		position.y = win->mousepos.y - radius;
		position.x = win->mousepos.x - radius;
	}
}

void Circle::mousedrag()
{
	if (!dragging)
	{
		offsetx = win->mousepos.x - position.x;
		offsety = win->mousepos.y - position.y;
	}
	position.x = win->mousepos.x - offsetx;
	position.y = win->mousepos.y - offsety;
}

void Circle::update()
{
	if (win->clicked && !win->dragging)
	{
		if (mouseover())
		{
			dragging = 1;
			win->dragging = 1;
		}
	}
	else if (!win->clicked)
	{
		win->dragging = 0;
		dragging = 0;
	}

	mousedrag();
	//mousecenter();

	circle.setPosition(position);
}

void Circle::highlight(sf::Color color)
{
	circle.setOutlineThickness(3);
	circle.setOutlineColor(color);
}

void Circle::unhighlight()
{
	circle.setOutlineThickness(0);
	circle.setOutlineColor(color); // just in case
}

void Circle::draw()
{
	win->window->draw(circle);
}

// DO NOT CALL UPDATE INSIDE ZORDER OR IT WILL BE RECURSIVE
void zorder(Win& win)
{
	//win.ordered = 1;
	bool reorder = 0;
	Shape* temp = NULL;

	for (int i = win.zindex - 1; i > 0; i--) // intentionally ignore 0
	{
		if (win.zlist[i]->dragging)
		{
			temp = win.zlist[i];
			reorder = 1;
		}

		if (reorder)
			win.zlist[i] = win.zlist[i - 1];

	}

	if (reorder)
		win.zlist[0] = temp;
}

void zdraw(Win& win)
{
	for (int i = 0; i <= win.zindex - 1; i++)
	{
		win.zlist[i]->update();
	}

	for (int i = win.zindex - 1; i >= 0; i--)
	{
		win.zlist[i]->draw();
	}
}