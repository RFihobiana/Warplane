#include "utilities.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include <cmath>
#include <numbers>
#include <string>


std::string to_string(const sf::Keyboard::Key key) {
    #define KEY_TO_STRING(KEY)  \
        case sf::Keyboard::KEY: \
            return #KEY;

    switch (key) {
        KEY_TO_STRING(Unknown)
        KEY_TO_STRING(A)
        KEY_TO_STRING(B)
        KEY_TO_STRING(C)
        KEY_TO_STRING(D)
        KEY_TO_STRING(E)
        KEY_TO_STRING(F)
        KEY_TO_STRING(G)
        KEY_TO_STRING(H)
        KEY_TO_STRING(I)
        KEY_TO_STRING(J)
        KEY_TO_STRING(K)
        KEY_TO_STRING(L)
        KEY_TO_STRING(M)
        KEY_TO_STRING(N)
        KEY_TO_STRING(O)
        KEY_TO_STRING(P)
        KEY_TO_STRING(Q)
        KEY_TO_STRING(R)
        KEY_TO_STRING(S)
        KEY_TO_STRING(T)
        KEY_TO_STRING(U)
        KEY_TO_STRING(V)
        KEY_TO_STRING(W)
        KEY_TO_STRING(X)
        KEY_TO_STRING(Y)
        KEY_TO_STRING(Z)
        KEY_TO_STRING(Num0)
        KEY_TO_STRING(Num1)
        KEY_TO_STRING(Num2)
        KEY_TO_STRING(Num3)
        KEY_TO_STRING(Num4)
        KEY_TO_STRING(Num5)
        KEY_TO_STRING(Num6)
        KEY_TO_STRING(Num7)
        KEY_TO_STRING(Num8)
        KEY_TO_STRING(Num9)
        KEY_TO_STRING(Escape)
        KEY_TO_STRING(LControl)
        KEY_TO_STRING(LShift)
        KEY_TO_STRING(LAlt)
        KEY_TO_STRING(LSystem)
        KEY_TO_STRING(RControl)
        KEY_TO_STRING(RShift)
        KEY_TO_STRING(RAlt)
        KEY_TO_STRING(RSystem)
        KEY_TO_STRING(Menu)
        KEY_TO_STRING(LBracket)
        KEY_TO_STRING(RBracket)
        KEY_TO_STRING(Semicolon)
        KEY_TO_STRING(Comma)
        KEY_TO_STRING(Period)
        KEY_TO_STRING(Apostrophe)
        KEY_TO_STRING(Slash)
        KEY_TO_STRING(Backslash)
        KEY_TO_STRING(Grave)
        KEY_TO_STRING(Equal)
        KEY_TO_STRING(Hyphen)
        KEY_TO_STRING(Space)
        KEY_TO_STRING(Enter)
        KEY_TO_STRING(Backspace)
        KEY_TO_STRING(Tab)
        KEY_TO_STRING(PageUp)
        KEY_TO_STRING(PageDown)
        KEY_TO_STRING(End)
        KEY_TO_STRING(Home)
        KEY_TO_STRING(Insert)
        KEY_TO_STRING(Delete)
        KEY_TO_STRING(Add)
        KEY_TO_STRING(Subtract)
        KEY_TO_STRING(Multiply)
        KEY_TO_STRING(Divide)
        KEY_TO_STRING(Left)
        KEY_TO_STRING(Right)
        KEY_TO_STRING(Up)
        KEY_TO_STRING(Down)
        KEY_TO_STRING(Numpad0)
        KEY_TO_STRING(Numpad1)
        KEY_TO_STRING(Numpad2)
        KEY_TO_STRING(Numpad3)
        KEY_TO_STRING(Numpad4)
        KEY_TO_STRING(Numpad5)
        KEY_TO_STRING(Numpad6)
        KEY_TO_STRING(Numpad7)
        KEY_TO_STRING(Numpad8)
        KEY_TO_STRING(Numpad9)
        KEY_TO_STRING(F1)
        KEY_TO_STRING(F2)
        KEY_TO_STRING(F3)
        KEY_TO_STRING(F4)
        KEY_TO_STRING(F5)
        KEY_TO_STRING(F6)
        KEY_TO_STRING(F7)
        KEY_TO_STRING(F8)
        KEY_TO_STRING(F9)
        KEY_TO_STRING(F10)
        KEY_TO_STRING(F11)
        KEY_TO_STRING(F12)
        KEY_TO_STRING(F13)
        KEY_TO_STRING(F14)
        KEY_TO_STRING(F15)
        KEY_TO_STRING(Pause)
        default:
            return "Unknown";
    }
        
}

float to_radian(const float degree) { return degree * std::numbers::pi / 180.f; }

float to_degree(const float radian) { return radian * 180.f / std::numbers::pi; }

sf::Vector2f normalized(const sf::Vector2f& vector) {
    float distance = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
    assert(distance != 0.f);
    return vector / distance;
}

float distance(const SceneNode& a, const SceneNode& b) {
    sf::Vector2f first_position = a.get_world_position();
    sf::Vector2f second_position = b.get_world_position();
    return sqrtf(
        std::pow(
            first_position.x - second_position.x,
            2
        ) + 
        std::pow(
            first_position.y - second_position.y, 
        2)
    );
}

float nearest_scene(const SceneNode& a, const SceneNode& b) {
    sf::Vector2f first_position = a.getPosition();
    sf::Vector2f second_position = b.getPosition();

    return
        (first_position.x - second_position.x) * (first_position.x - second_position.x) + // x**2
        (first_position.y - second_position.y) * (first_position.y - second_position.y);  // y**2
}


