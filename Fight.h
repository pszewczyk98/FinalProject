#include "Player.h"
#include "Menu.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class Fight
{
private:
	Player* player1;
	Player* fighter;
	bool isPlayerTurn;
public:
	Fight(Player* player, Player* enemy)
	{
		player1 = player;
		fighter = enemy;
		isPlayerTurn = true;
	}

	Player* getEnemy() { return fighter; }
	Player* getPlayer() { return player1; }

	void playerIsHit()
	{
		int damage = fighter->getStrength() + fighter->getEquipped().ReturnWeaponDamage();
		player1->takeDmg(damage);
		if (!(player1->getHp() <= 0))
			cout << "You were hit for " << damage << " damage!" << endl << "You have " << player1->getHp() << " health remaining." << endl;
		else
			player1->setDead(true);
	}
	void enemyIsHit()
	{
		int damage = player1->getEquipped().ReturnWeaponDamage();
		fighter->takeDmg(damage);
		if (!(fighter->getHp() <= 0))
			cout << "You hit the enemy for " << damage << " damage!" << endl << "They have " << fighter->getHp() << " health remaining." << endl;
		else
			fighter->setDead(true);
	}

	void fightSequence()
	{
		cout << endl << endl;
		cout << "You come across a " << fighter->getName() << ". Time to fight!" << endl << endl;
		while (true)
		{
			FightMenu attack;
			attack.acceptInput(player1);
			switch (player1->getMenuChoice())
			{
			case 11:
			case 12:
				if ((rand() % 100) < 80)
					enemyIsHit();
				else
					cout << "Enemy blocked your attack!" << endl;
				break;
			case 15:
				playerIsHit();
				break;
				
			}
			if (player1->getMenuChoice() == 15 || fighter->getIsDead())
				break;
			DefendMenu defend;
			defend.acceptInput(player1);
			if ((rand() % 100) < 50)
				playerIsHit();
			else
				cout << "You blocked the enemy's attack!" << endl;
			if (player1->getIsDead() || fighter->getIsDead())
				break;
		}
		if (fighter->getIsDead())
			cout << "You won the fight!" << endl;
		else if (player1->getMenuChoice() == 15)
			cout << "You ran away." << endl;
		else
			cout << "You won the fight!" << endl;
		fighter->setHp(fighter->getMaxHp());
		if(player1->getIsDead())
			player1->setHp(player1->getMaxHp());
		player1->setDead(false);
		fighter->setDead(false);
		cout << endl << endl;
	}
};