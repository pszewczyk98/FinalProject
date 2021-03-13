#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "MenuItems.h"

using namespace std;

class Menu
{
	
public:
	vector<shared_ptr<MenuItem>> allChoices;
	vector<shared_ptr<MenuItem>> currentChoices;
	Menu() { }
	~Menu() {}
	void clean()
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	string toString()
	{
		string s = "";
		vector<shared_ptr<MenuItem>>::iterator i;
		int k = 1;
		for (i = currentChoices.begin(); i != currentChoices.end(); ++i)
		{
			s += to_string(k) + ": " + (*i)->toString() + "\n";
			k++;
		}
		return s;
	}
	void acceptInput(Player* p)
	{
		cout << this->toString();
		int max = currentChoices.size();
		int input;
		while (true)
		{
			cout << "Choose an action: ";
			if (cin >> input && input > 0 && input <= max)
				break;
			cout << "Choose an action number 1-" << to_string(max) << "." << endl;
			clean();
		}
		clean();
		currentChoices[input-1]->action(p);
	}
	void addAllChoices(shared_ptr<MenuItem> c) { allChoices.push_back(c); }
};

class MainMenu : public Menu
{
public:
	MainMenu(Player* p, Map m)
	{
		currentChoices.push_back(make_shared<MoveMenuItem>());
		currentChoices.push_back(make_shared<InventoryMenuItem>());
		if (p->hasEquipped() || p->hasItem(3))
		{
			currentChoices.push_back(make_shared<UseItemMenuItem>());
		}
		if (m.currentRoom(p)->hasItem())
		{
			currentChoices.push_back(make_shared<InspectItemMenuItem>());
		}
		if (m.currentRoom(p)->hasAcquirable())
		{
			currentChoices.push_back(make_shared<PickUpMenuItem>());
		}
		if (m.currentRoom(p)->hasUsable())
		{
			currentChoices.push_back(make_shared<UseInRoomMenuItem>());
		}
	}
};

class MoveMenu : public Menu
{
public:
	MoveMenu() {}
	MoveMenu(vector<int> directions)
	{
		addAllChoices(make_shared<NorthMenu>());
		addAllChoices(make_shared<EastMenu>());
		addAllChoices(make_shared<SouthMenu>());
		addAllChoices(make_shared<WestMenu>());
		addAllChoices(make_shared<UpMenu>());
		addAllChoices(make_shared<DownMenu>());
		vector<int>::iterator i;
		for (i = directions.begin(); i != directions.end(); ++i)
		{
			currentChoices.push_back(allChoices[(*i)-1]);
		}
	}
};

class ItemMenu : public Menu
{
public:
	ItemMenu(vector<Item> items)
	{
		vector<Item>::iterator i;
		for (i = items.begin(); i != items.end(); ++i)
		{
			currentChoices.push_back(make_shared<ItemMenuItem>(*i));
		}
	}
};

class InvSubMenu : public Menu
{
public:
	InvSubMenu(Player* p)
	{
		if (p->getInv().size() != 0)
		{
			currentChoices.push_back(make_shared<InspectItemMenuItem>());
			currentChoices.push_back(make_shared<DropMenuItem>());
		}
		if (p->hasEquippable())
		{
			currentChoices.push_back(make_shared<EquipMenuItem>());
		}
		if (p->hasEquipped() || p->hasArmor())
		{
			currentChoices.push_back(make_shared<UnequipMenuItem>());
		}
		currentChoices.push_back(make_shared<ExitMenuItem>());
	}
};

class FightMenu : public Menu
{
public:
	FightMenu()
	{
		currentChoices.push_back(make_shared<AttackHighMenu>());
		currentChoices.push_back(make_shared<AttackLowMenu>());
		currentChoices.push_back(make_shared<RunAwayMenu>());
	}
};

class DefendMenu : public Menu
{
public:
	DefendMenu()
	{
		currentChoices.push_back(make_shared<DefendHighMenu>());
		currentChoices.push_back(make_shared<DefendLowMenu>());
	}
};