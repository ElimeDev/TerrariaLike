#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Input
{
    struct Button { bool left, right, up, down, attack, escape; };

public:
    // prototype du constructeur
    Input();
    //Proto Getbtn
    Button GetButton(void) const;
    //proto
    void InputHandler(Event event, RenderWindow& window);

private:
    Button button;

};
