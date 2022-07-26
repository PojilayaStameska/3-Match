#pragma once

#include <random>
#include <vector>


class Rng
{
public:
	explicit Rng(unsigned int seed = std::random_device()());

	void reset();
	void setSeed(unsigned int seed);
	unsigned int getSeed() const;

	int getInt(int exclusiveMax);
	int getInt(int min, int inclusiveMax);

	bool getBool(double probability = 0.5);
	float getFloat(float min, float max); 

	int rollDice(int n, int s); 

	template <typename T>
	const T& getOne(const std::vector<T>& vector);

	template <typename T>
	void shuffle(std::vector<T>& vector);

private:
	unsigned int seed;
	std::mt19937 mt;
};

template <typename T>
const T& Rng::getOne(const std::vector<T>& vector)
{
	return vector[getInt(vector.size())];
}

template <typename T>
void Rng::shuffle(std::vector<T>& vector)
{
	std::shuffle(vector.begin(), vector.end(), mt);
}
