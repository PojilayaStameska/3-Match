#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <algorithm> 

int odd(int number);
int even(int number);

int randomInt(int exclusiveMax);
int randomInt(int min, int inclusiveMax); 

int length(const sf::Vector2i& vector);
int lengthSquared(const sf::Vector2i& vector);

std::vector<sf::Vector2i> getLine(const sf::Vector2i& from, const sf::Vector2i& to, bool orthogonalSteps = false);

template <typename T>
int sign(T value)
{
	return (value > static_cast<T>(0)) - (value < static_cast<T>(0));
}

template <typename T>
inline T clamp(T value, T min, T max)
{
	return std::max(min, std::min(value, max));
}
