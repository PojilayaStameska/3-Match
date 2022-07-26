#pragma once
#include "../Entity.hpp"
#include "../Hero.hpp"
class Enemy : public Entity
{

public:
	virtual void die() override;
protected:

private:
};