#pragma once
#include<string>
#include "Player.h"

using namespace std;

class MenuItem
{
private:
	string description;

public:
	MenuItem() {}
	MenuItem(string d)
	{
		setDescription(d);
	}
	string getDescription() { return description; }
	void setDescription(string d) { description = d; }

	virtual void action(Player* p) {}

	string toString()
	{
		return description;
	}

};

class NorthMenu : public MenuItem
{
public:
	NorthMenu(){setDescription("North");}
	void action(Player* p){p->setY(p->getY() + 1);}
};

class SouthMenu : public MenuItem
{
public:
	SouthMenu() { setDescription("South"); }
	void action(Player* p) { p->setY(p->getY() - 1);}
};

class EastMenu : public MenuItem
{
public:
	EastMenu() { setDescription("East"); }
	void action(Player* p) { p->setX(p->getX() + 1); }
};

class WestMenu : public MenuItem
{
public:
	WestMenu() { setDescription("West"); }
	void action(Player* p) { p->setX(p->getX() - 1); }
};

class UpMenu : public MenuItem
{
public:
	UpMenu() { setDescription("Up"); }
	void action(Player* p) { p->setZ(p->getZ() + 1); }
};

class DownMenu : public MenuItem
{
public:
	DownMenu() { setDescription("Down"); }
	void action(Player* p) { p->setZ(p->getZ() - 1); }
};

class MoveMenuItem : public MenuItem
{
public:
	MoveMenuItem() { setDescription("Move"); }
	void action(Player* p) { p->setMenuChoice(1); }
};

class InspectItemMenuItem : public MenuItem
{
public:
	InspectItemMenuItem() { setDescription("Inspect item"); }
	void action(Player* p) { p->setMenuChoice(2); }
};

class InventoryMenuItem : public MenuItem
{
public:
	InventoryMenuItem() { setDescription("Inventory"); }
	void action(Player* p) { p->setMenuChoice(3); }
};

class UseItemMenuItem : public MenuItem
{
public:
	UseItemMenuItem() { setDescription("Use item"); }
	void action(Player* p) { p->setMenuChoice(4); }
};

class PickUpMenuItem : public MenuItem
{
public:
	PickUpMenuItem() { setDescription("Pick up item"); }
	void action(Player* p) { p->setMenuChoice(5); }
};

class ItemMenuItem : public MenuItem
{
public:
	int id;
	ItemMenuItem(Item x) { setDescription(x.getName()); id = x.getId(); }
	void action(Player* p) { p->setMenuChoice(id); }
};

class DropMenuItem : public MenuItem
{
public:
	DropMenuItem() { setDescription("Drop item"); }
	void action(Player* p) { p->setMenuChoice(6); }
};

class EquipMenuItem : public MenuItem
{
public:
	EquipMenuItem() { setDescription("Equip item"); }
	void action(Player* p) { p->setMenuChoice(7); }
};

class UnequipMenuItem : public MenuItem
{
public:
	UnequipMenuItem() { setDescription("Unequip item"); }
	void action(Player* p) { p->setMenuChoice(8); }
};

class ExitMenuItem : public MenuItem
{
public:
	ExitMenuItem() { setDescription("Exit"); }
	void action(Player* p) { p->setMenuChoice(9); }
};

class UseInRoomMenuItem : public MenuItem
{
public:
	UseInRoomMenuItem() { setDescription("Use item in room"); }
	void action(Player* p) { p->setMenuChoice(10); }
};

class AttackHighMenu : public MenuItem
{
public:
	AttackHighMenu() { setDescription("Attack high"); }
	void action(Player* p) { p->setMenuChoice(11); }
};

class AttackLowMenu : public MenuItem
{
public:
	AttackLowMenu() { setDescription("Attack low"); }
	void action(Player* p) { p->setMenuChoice(12); }
};

class DefendHighMenu : public MenuItem
{
public:
	DefendHighMenu() { setDescription("Defend high"); }
	void action(Player* p) { p->setMenuChoice(13); }
};

class DefendLowMenu : public MenuItem
{
public:
	DefendLowMenu() { setDescription("Defend low"); }
	void action(Player* p) { p->setMenuChoice(14); }
};

class RunAwayMenu : public MenuItem
{
public:
	RunAwayMenu() { setDescription("Run away"); }
	void action(Player* p) { p->setMenuChoice(15); }
};
