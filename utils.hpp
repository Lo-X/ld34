#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <resources/animation.hpp>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Helpers to set the origin of sprites/text/... at center
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(Animation& animation);

// Math
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);
float distance(const sf::Vector2f &lhs, const sf::Vector2f &rhs);

// Random number generation
int     randomInt(int min, int max);
float   randomFloat(float min, float max);

#include <utils.inl>

#endif // UTILS_H
