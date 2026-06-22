#include "Input.h"

//Constructeur
Input::Input()
{
    button.left = button.right = button.jump = button.attack = button.escape = false;
}

// Fonction qui accede à button (struc) et nous donne l'info private
Input::Button Input::getButton(void) const
{
    return button;
}

//fonction de gestion des input
void Input::InputHandler(Event event, RenderWindow& window)
{
    if (event.type == Event::Closed)
    {
        window.close();
    }

    //Gestion des input clavier/souris
    //Detection bouton appuyé
    if (event.type == Event::KeyPressed)
    {
        switch (event.key.code)// Code de la touche utilisée
        {
        case Keyboard::Escape:
            button.escape = true;
            break;
        case Keyboard::Q:
            button.left = true;
            break;
        case Keyboard::D:
            button.right = true;
            break;
        case Keyboard::Z:
            button.jump = true;
            break;
        case Keyboard::Space:
            button.attack = true;
            break;
        default:
            break;
        }
    }
    //Detection des boutons relaches
    if (event.type == Event::KeyReleased)
    {
        switch (event.key.code)// Code de la touche utilisée
        {
        case Keyboard::Escape:
            button.escape = false;
            break;
        case Keyboard::Q:
            button.left = false;
            break;
        case Keyboard::D:
            button.right = false;
            break;
        case Keyboard::Z:
            button.jump = false;
            break;
        case Keyboard::Space:
            button.attack = false;
            break;
        default:
            break;
        }
    }
}