#pragma once

#include <vector>
#include "Item.h"
#include "Room.h"

using namespace std;

class Player
{
private:
	bool isDead;
	int x, y, z, hp, maxHp, strength;
	vector<Item> inventory;
	Item equipped, armor;
	int menuChoice;
	string name;
public:
	~Player() {}
	Player() {}
	Player(string n, int initX, int initY, int initZ, vector<Item> inv, int hp, int str) 
	{
		setName(n);
		setX(initX);
		setY(initY);
		setZ(initZ);
		setInv(inv);
		setEquipped(Item("NULL", "NULL", 0, 0, false, false));
		setArmor(Item("NULL", "NULL", 0, 0, false, false));
		setHp(hp);
		setMaxHp(hp);
		isDead = false;
		setStrength(str);
	}

	vector<Item> getInv() { return inventory; }
	int getX() { return x; }
	int getY() { return y; }
	int getZ() { return z; }
	Item getEquipped() { return equipped; }
	Item getArmor() { return armor; }
	int getMenuChoice() { return menuChoice; }
	int getHp() { return hp; }
	int getMaxHp() { return maxHp; }
	int getStrength() { return strength; }
	string getName() { return name; }

	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
	void setZ(int newZ) { z = newZ; }
	void setInv(vector<Item> inv) { inventory = inv; }
	void setHp(int newHp) { hp = newHp; }
	void setMaxHp(int max) { maxHp = max; }
	void setStrength(int newStrength) { strength = newStrength; }
	void setName(string n) { name = n; }
	void setEquipped(Item e)
	{ 
		if (hasEquipped())
			addItem(getEquipped());
		equipped = e; 
		deleteItem(e.getId());
	}
	bool takeDmg(int oppStrength)
	{
		int dmg = oppStrength - getArmor().getDef();
		setHp(getHp() - dmg);
		if (hp <= 0)
			return true;
		else
			return false;
	}
	void setArmor(Item a) 
	{
		if (hasArmor())
			addItem(getArmor());
		armor = a;
		deleteItem(a.getId());
	}
	void setMenuChoice(int mc) { menuChoice = mc; }

	bool hasArmor() { return getArmor().getId() != 0; }
	bool hasEquipped() { return getEquipped().getId() != 0; }

	void addItem(Item add) { inventory.push_back(add); }
	void deleteItem(int deleted)
	{
		vector<Item>::iterator i;
		for (i = inventory.begin(); i != inventory.end(); ++i)
		{
			if ((*i).getId() == deleted)
			{
				inventory.erase(i);
				break;
			}
		}
	}

	bool hasEquippable()
	{
		vector<Item>::iterator i;
		if (inventory.size() == 0)
			return false;
		for (i = inventory.begin(); i != inventory.end(); ++i)
		{
			if ((*i).getEquippable() || (*i).getIsArmor())
				return true;
		}
		return false;
	}

	void unequip(){setEquipped(Item("NULL", "NULL", 0, 0, false, false));}

	void unequipArmor(){setArmor(Item("NULL", "NULL", 0, 0, false, false));}

	vector<Item> equippableItems()
	{
		if (!hasEquippable())
			return vector<Item>();
		vector<Item> equippables;
		vector<Item>::iterator i;
		for (i = inventory.begin(); i != inventory.end(); ++i)
		{
			if ((*i).getEquippable() || (*i).getIsArmor())
				equippables.push_back(*i);
		}
		return equippables;
	}

	bool hasItem(int itemId)
	{
		vector<Item>::iterator i;
		for (i = inventory.begin(); i != inventory.end(); ++i)
		{
			if ((*i).getId() == itemId)
				return true;
		}
		return false;
	}

	Item idSearch(int idCheck)
	{
		vector<Item>::iterator i;
		for (i = inventory.begin(); i != inventory.end(); ++i)
		{
			if ((*i).getId() == idCheck)
				return (*i);
		}
		return Item();
	}

	string invList()
	{
		string s;
		if (inventory.size() != 0)
		{
			s += "Items in inventory:\n";
			vector<Item>::iterator i;
			for (i = inventory.begin(); i != inventory.end(); ++i)
			{
				s += (*i).getName() + "\n";
			}
		}
		return s;
	}
	string itemReport()
	{
		string s = "";
		if (inventory.size() == 0 && !hasEquipped() && !hasArmor())
			return "No items in inventory.\n";
		if (hasArmor())
			s += "Armor: " + getArmor().getName() + "\n";
		if (hasEquipped())
			s += "Equipped Item: " + getEquipped().getName() + "\n";
		s += invList();
		return s;
	}

	vector<Item> usables()
	{
		vector<Item> u;
		vector<Item>::iterator i;
		for (i = inventory.begin(); i != inventory.end(); ++i)
		{
			if ((*i).getUsableInRoom())
			{
				u.push_back(*i);
			}
		}
		return u;
	}

	bool getIsDead() { return isDead; }

	void setDead(bool d) { isDead = d; }
};

class Enemy : public Player
{
public:
	Enemy(string n, int hp, int strength, Item weapon, Item ar) : Player(n, 0, 0, 0, vector<Item>(), hp, strength)
	{
		setEquipped(weapon);
		setArmor(ar);
	}


};