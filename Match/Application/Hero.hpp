#pragma once
#include "Entity.hpp"
#include "../TileEnum.hpp"
#include <iostream>
#include "../Utility/Rng.hpp"

#include <atomic>
#include <map>


class Hero: public Entity
{
public:
	Hero();
	bool getAliveState();
	virtual void die() override;

	int Points();
	void setPoints(int points);

	float Wallet();
	void setWallet(float setValue);

	int Shield();
	void setShield(int setValue);

	float Time() { return timeToMove; };
	bool setTime(float setValue);

	float Cooldown() { return turnCooldown; };
	bool setCooldown(float setValue) { if (setValue < 0) { turnCooldown = 0; return true; }; turnCooldown = setValue; return false; };

	int TurnResult(Tile key) { return turnResult[key]; };
	void setTernResult(Tile key, int newValue) { turnResult[key] = newValue; }

	void attack(Entity* monster) override;
	void endTurn();


	float FireDamage() { return fireDamage; }
	float ThunderDamage() { return thunderDamage; }
	float ThunderSelfCastChange() { return thunderSelfCastChange; }
	float CloverEffect() { return cloverEffect; }
	float ShieldEffect() { return shieldEffect; }
	float HeartEffect() { return heartEffect; }

	void setFireDamage(float setValue) { fireDamage = setValue; }
	void setThunderDamage(float setValue) { thunderDamage = setValue; }
	void setThunderSelfCastChange(float setValue) { thunderSelfCastChange = setValue; }
	void setCloverEffect(float setValue) { cloverEffect = setValue; }
	void setShieldEffect(float setValue) { shieldEffect = setValue; }
	void setHeartEffect(float setValue) { heartEffect = setValue; }

	float ThunderEnemyResult() { return thunderEnemyResult; }
	float ThunderSelfResult() { return thunderSelfResult; }

	int UnRealizeDmg() { return unRealizeDmg;}
	void setUnrealizeDmg(int value) { unRealizeDmg = value; };

	void clearTurnResult();

	bool IsTurnEnd() { return isTurnEnd; }
	void setIsTurnEnd(bool value) { isTurnEnd = value; }

private:



	Rng rng;

	std::map <Tile, int> turnResult;
	float fireDamage = 1, thunderDamage = 2, thunderSelfCastChange = 0.3, cloverEffect = 0.01, shieldEffect = 1, heartEffect = 2;
	float thunderEnemyResult = 0, thunderSelfResult = 0;
	bool isAlive;
	float wallet, timeToMove = 10, turnCooldown = 0;
	int points, shield, unRealizeDmg;
	std::atomic_bool isTurnEnd;
};