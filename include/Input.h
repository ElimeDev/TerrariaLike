#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Input
{
    struct Button { bool left, right, jump, attack, escape; };

public:
    // prototype du constructeur
    Input();
    //Proto Getbtn
    Button getButton(void) const;
    //proto
    void InputHandler(Event event, RenderWindow& window);

private:
    Button button;
};
