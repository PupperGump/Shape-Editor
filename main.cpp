#include <Shape Editor.h>

// assuming a starting point is set beforehand
std::chrono::duration<float> getFrameTime(std::chrono::steady_clock::time_point& start)
{
	auto end = std::chrono::high_resolution_clock::now();
	auto dur = end - start;
	start = std::chrono::high_resolution_clock::now(); // reset

	return dur;
}

unsigned int getFramesPerSecond(std::chrono::steady_clock::time_point& start)
{
	auto spf = getFrameTime(start); // seconds per frame

	unsigned int fps = 1 / spf.count();

	return fps;
}

int main()
{
	sf::RenderWindow window;
	sf::Event vent;

	window.create({ 1920, 1080, 32 }, "Shape Editor", sf::Style::Default);
	window.setSize({ 500, 500 });
	window.setFramerateLimit(144u);

	auto time = std::chrono::high_resolution_clock::now();

	Win win(window);
	//std::cout << "Inside main: " << &window << "\n";
	//std::cout << "Inside Win: " << &*&*&*&*&*&win.window << "\n";

	Rect rect(win, { 0, 0 }, { 200, 200 }, sf::Color::Red);
	//Rect rect2(win, { 100, 100 }, { 200, 200 }, sf::Color::Green);
	//Rect rect3(win, { 100, 100 }, { 200, 200 }, sf::Color::Blue);
	//Rect rect4(win, { 100, 100 }, { 200, 200 }, sf::Color::Yellow);
	//Rect rect5(win, { 100, 100 }, { 200, 200 }, sf::Color::Magenta);
	//Circle circle(win, { 110, 110 }, 100, sf::Color::Green);

	std::vector<Rect> rectlist;
	//rectlist[0] = { win };
	//std::cout << rectlist[0].position.x << ", " << rectlist[0].position.y << "\n";
	int rectlistcounter = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(vent))
		{
			switch (vent.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(window.getDefaultView());
				break;

			case sf::Event::KeyPressed:
				switch (vent.key.code)
				{
				case sf::Keyboard::Key::Escape:
					window.close();
					break;
				case sf::Keyboard::Key::F11: // borderless fullscreen
					if (!win.fullscreen)
					{
						win.lastsize = window.getSize();
						win.lastposition = window.getPosition();
						window.setPosition({ -8, -31 });
						window.setSize({ 1920, 1080 });
					}
					else
					{
						window.setPosition(win.lastposition);
						window.setSize(win.lastsize);
					}
					win.fullscreen = !win.fullscreen;
					break;

					// shape control
				case sf::Keyboard::Key::R:
					rectlist[0] = rect;
					//win.zlist.emplace_back(rectlist[rectlistcounter++]);
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (vent.mouseButton.button)
				{
				case sf::Mouse::Left:
					win.clicked = 1;
					break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				switch (vent.mouseButton.button)
				{
				case sf::Mouse::Left:
					win.clicked = 0;
					break;
				}
				break;
			}
		}
		win.mouseposition();

		window.clear({ 0, 0, 0, 0 });
		zorder(win);

		win.zlist[0]->highlight(sf::Color::White);
		if (win.clicked && !win.zlist[0]->dragging)
			win.zlist[0]->unhighlight();
		
		zdraw(win);
		window.display();

		//std::cout << getFrameTime(start).count() << "\n";
		//std::cout << getFramesPerSecond(time) << "\n";
	}
	return 0;
}