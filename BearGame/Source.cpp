#include <SFML/Graphics.hpp>
using namespace sf;

// test function: create empty window
int main()
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}