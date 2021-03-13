#include <iostream>
#include <time.h>
#include <stdio.h>
#include "Room.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "Fight.h"

using namespace std;


int main() {
	Lab lab;
	vector<Item> startingInv;
	Player player1("You", 0, 4, 0, startingInv, 100, 10);
	Player* playerptr = &player1;
	srand((unsigned int)time(NULL));

	
	while (true)
	{
		bool correctRoom = false;
		bool correctItems = false;
		if (player1.getX() == 0 && player1.getY() == 5 && player1.getZ() == 0)
		{
			correctRoom = true;
		}
		if (player1.hasItem(4) && player1.hasItem(2))
		{
			correctItems = true;
		}
		Room* current = lab.currentRoom(playerptr);
		cout << current->toString();
		MainMenu firstMenu(playerptr, lab);
		firstMenu.acceptInput(playerptr);
		MoveMenu movement(lab.directionsAvailable(*current));
		InvSubMenu invMenu(playerptr);
		vector<Item> equip = player1.equippableItems();
		
		switch(player1.getMenuChoice())
		{
		case 1:
			movement.acceptInput(playerptr);
			break;
		case 2:
			if (current->getItems().size() == 1)
				cout << current->getItems()[0].getDescription();
			else
			{
				ItemMenu inspect(current->getItems());
				inspect.acceptInput(playerptr);
				cout << current->idSearch(player1.getMenuChoice()).getDescription() << endl;
			}
			break;
		case 3:
			cout << player1.itemReport();
			
			invMenu.acceptInput(playerptr);
			switch (player1.getMenuChoice())
			{
			case 2:
				if (player1.getInv().size() == 1)
					cout << player1.getInv()[0].getDescription();
				else
				{
					ItemMenu inspectInv(player1.getInv());
					inspectInv.acceptInput(playerptr);
					cout << player1.idSearch(player1.getMenuChoice()).getDescription() << endl;
				}
				break;
			case 6:
				if (player1.getInv().size() == 1)
					lab.dropItem(playerptr, player1.getInv()[0].getId());
				else
				{
					ItemMenu dropFromInv(player1.getInv());
					dropFromInv.acceptInput(playerptr);
					lab.dropItem(playerptr, player1.getMenuChoice());
				}
				break;
			case 7:
				if (equip.size() == 1)
					if (equip[0].getEquippable())
						player1.setEquipped(equip[0]);
					else
						player1.setArmor(equip[0]);
				else
				{
					ItemMenu equipFromInv(equip);
					equipFromInv.acceptInput(playerptr);
					Item toBeEquipped = player1.idSearch(player1.getMenuChoice());
					if (toBeEquipped.getIsArmor())
						player1.setArmor(toBeEquipped);
					else
						player1.setEquipped(toBeEquipped);
				}
				break;
			case 8:
				if (player1.hasArmor() && player1.hasEquipped())
				{
					vector<Item> equipped;
					equipped.push_back(player1.getArmor());
					equipped.push_back(player1.getEquipped());
					ItemMenu unequipItem(equipped);
					unequipItem.acceptInput(playerptr);
					if (player1.getArmor().getId() == player1.getMenuChoice())
						player1.unequipArmor();
					else
						player1.unequip();
				}
				else if (player1.hasEquipped())
					player1.unequip();
				else
					player1.unequipArmor();
				break;
			default:
				break;
			}
			break;
		case 4:
			if (player1.usables().size() == 1)
			{
				if (player1.usables()[0].useItem(correctRoom, correctItems))
				{
					lab.success(player1.usables()[0].getId());
				}
			}
			else
			{
				ItemMenu use(player1.usables());
				use.acceptInput(playerptr);
				if (player1.idSearch(player1.getMenuChoice()).useItem(correctRoom, correctItems))
					lab.success(player1.getMenuChoice());
			}
			break;
		case 5:
			if (current->acquirables().size() == 1)
			{
				player1.addItem(current->acquirables()[0]);
				lab.currentRoom(playerptr)->deleteItem(current->acquirables()[0].getId());
			}
			else
			{
				ItemMenu pickUp(current->acquirables());
				pickUp.acceptInput(playerptr);
				player1.addItem(current->idSearch(player1.getMenuChoice()));
				lab.currentRoom(playerptr)->deleteItem(player1.getMenuChoice());
			}
			break;
		case 10:
			if (current->usables().size() == 1)
			{
				if (current->usables()[0].useItem(correctRoom, correctItems))
				{
					lab.success(current->usables()[0].getId());
				}
			}
			else
			{
				ItemMenu use(current->usables());
				use.acceptInput(playerptr);
				if (current->idSearch(player1.getMenuChoice()).useItem(correctRoom, correctItems))
					lab.success(player1.getMenuChoice());
			}
			break;
		}

		if (lab.win)
			break;

		if ((rand() % 100) < 20)
		{
			Fight encounter(playerptr, lab.selectRandomEnemy());
			encounter.fightSequence();
		}
		if(player1.getHp() < 98)
			playerptr->takeDmg(-3);
		cout << endl << endl << endl;
	}
	cout << "You won the game!" << endl;
}