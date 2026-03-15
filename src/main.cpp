#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main ()
{
	RenderWindow window(VideoMode(800, 600), "SFML works!");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
	}
	return 0;
}