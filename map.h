#pragma once

#include "Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

class Route
{
private:
	Room starting, destination;
public:
	Route(Room start, Room end)
	{
		starting = start;
		destination = end;
	}

	Room getStarting() { return starting; }
	Room getDestination() { return destination; }

	friend bool operator == (const Route x, const Route y)
	{
		if (x.starting == y.starting && x.destination == y.destination)
			return true;
		else
			return false;
	}
};

class Direction
{
private:
	int num;
	string direction;
public:
	Direction(int n, string d)
	{
		setNum(n);
		setDirection(d);
	}

	int getNum() { return num; }
	string getDirection() { return direction; }
	void setNum(int n) { num = n; }
	void setDirection(string d) { direction = d; }
};

class Map
{
private:
	vector<Route> routes;
	vector<Direction> directionNums;

public:
	vector<Enemy> availableEnemies;
	Room rooms[9][9][3];
	bool win;
	Map()
	{
		win = false;

	}
	~Map() {}

	void addEnemy(Enemy e)
	{
		availableEnemies.push_back(e);
	}

	void addRoom(Room r)
	{
		rooms[r.getX()][r.getY()][r.getZ()] = r;
		directionNums = { Direction(1, "North"), Direction(2, "East"), Direction(3, "South"), Direction(4, "West"), Direction(5, "Up"), Direction(6, "Down") };
	}
	void addRoute(Room x, Room y)
	{
		routes.push_back(Route(x, y));
	}
	
	void deleteRoute(Room x, Room y)
	{
		vector<Route>::iterator i;
		Route comparison(x, y);
		for (i = routes.begin(); i != routes.end(); ++i)
		{
			if(*i == comparison)
			{
				routes.erase(i);
				break;
			}
		}
	}

	bool verifyRoute(Room x, Room y)
	{
		vector<Route>::iterator i;
		Route comparison(x, y);
		for (i = routes.begin(); i != routes.end(); ++i)
		{
			if (*i == comparison)
			{
				return true;
			}
		}
		return false;
	}

	//Returns a vector of available directions from a room given as integers specified below in the direction method
	vector<int> directionsAvailable(Room start)
	{
		vector<int> directions;
		vector<Room> possible;
		vector<Route>::iterator i;
		vector<Room>::iterator j;
		for (i = routes.begin(); i != routes.end(); ++i)
		{
			if ((*i).getStarting() == start)
				possible.push_back((*i).getDestination());
		}
		for (j = possible.begin(); j != possible.end(); ++j)
		{
			directions.push_back(direction(start, *j));
		}
		sort(directions.begin(), directions.end());
		return directions;
	}

	string printAvailable(vector<int> directions)
	{
		string s = "";
		vector<int>::iterator i;
		vector<Direction>::iterator j;
		int k = 1;
		for (i = directions.begin(); i != directions.end(); ++i)
		{
			for (j = directionNums.begin(); j != directionNums.end(); ++j)
			{
				if ((*i) == (*j).getNum())
				{
					s += (to_string(k) + ": " + (*j).getDirection() + "\n");
					k++;
					break;
				}
			}
		}
		return s;
	}

	void mutualRoute(Room a, Room b)
	{
		addRoute(a, b);
		addRoute(b, a);
	}


	//1: North, 2: East, 3: South, 4: West, 5: Up, 6: Down
	int direction(Room start, Room end)
	{
		if (start.getX() == end.getX())
		{
			if (start.getY() == end.getY())
			{
				if (start.getZ() > end.getZ())
					return 6;
				else
					return 5;
			}
			else
			{
				if (start.getY() > end.getY())
					return 3;
				else
					return 1;
			}
		}
		else
		{
			if (start.getX() > end.getX())
				return 4;
			else
				return 2;
		}
	}

	void dropItem(Player* p, int itemId)
	{
		currentRoom(p)->AddItem(p->idSearch(itemId));
		p->deleteItem(itemId);
	}

	Room* currentRoom(Player* p) { return &rooms[p->getX()][p->getY()][p->getZ()]; }
	Room toNorth(int x, int y, int z){return rooms[x][y + 1][z];}

	Room toSouth(int x, int y, int z){return rooms[x][y - 1][z];}

	Room toWest(int x, int y, int z){return rooms[x - 1][y][z];}
	
	Room toEast(int x, int y, int z){return rooms[x + 1][y][z];}

	Room up(int x, int y, int z){return rooms[x][y][z + 1];}

	Room down(int x, int y, int z){return rooms[x][y][z - 1];}

	Enemy* selectRandomEnemy()
	{
		int randomNum = rand() % availableEnemies.size();
		return &availableEnemies[randomNum];
	}


};

class Lab : public Map
{
public:
	Lab()
	{
		Crossbow crossbow1;
		Pistol pistol1;
		addEnemy(Enemy("Crossbowman", 20, 5, crossbow1, Item("NULL", "NULL", 0, 0, false, false)));
		addEnemy(Enemy("a man carrying a pistol", 20, 5, pistol1, Item("NULL", "NULL", 0, 0, false, false)));
		Item laptop("Laptop", "An old, beat-up laptop computer. The display no longer works.", 4, 0, false, false);
		Item flashdrive("Flash Drive", "A 64 GB flashdrive with a label that says 'KEY'", 2, 0, false, false);
		Item hdmiCable("HDMI Cable", "A 12-foot long HDMI cable.", 3, 0, false, false, true, true);
		Item keypad("Keypad", "A keypad with keys for digits 0-9 and an enter button.", 1, 0, false, false, false, true);
		Item coat("Coat", "A heavy coat from the dead guy you found.", 5, 1, false, true);
		Item knife("Rusty Knife", "A rusty knife you found on the ground.", 6, 0, true, false, true, true);
		vector<Item> deadGuyRoomItems, laptopRoomItems, keypadRoomItems, knifeRoomItems, hdmiRoomItems, flashDriveRoomItems;
		laptopRoomItems.push_back(laptop);
		flashDriveRoomItems.push_back(flashdrive);
		keypadRoomItems.push_back(keypad);
		hdmiRoomItems.push_back(hdmiCable);
		deadGuyRoomItems.push_back(coat);
		knifeRoomItems.push_back(knife);
		addRoom(Room("Starting Room", "Around you are a few desks and some strange looking equipment that you have no idea how to use. \nThere are doors to the south and north.", vector<Item>(), 0, 4, 0));
		addRoom(Room("Projector Room", "There is one empty desk in this room. \nOn the ceiling is a projector.", vector<Item>(), 0, 5, 0));
		addRoom(Room("Keypad Room", "You find yourself in a hallway.\nThere are three doors, the southern one has a keypad next to it.", keypadRoomItems, 1, 5, 0));
		addRoom(Room("Hallway 1", "You find yourself in a hallway.\nThere are two doors.\nYou notice someone tracked blood down this hallway.", vector<Item>(), 1, 6, 0));
		addRoom(Room("Hallway 2", "You find yourself in a hallway.\nThere are three doors.\nThere is blood tracked through the door to the west.", vector<Item>(), 1, 7, 0));
		addRoom(Room("Dead Guy Room", "In this room is a man lying dead on the floor.\nHe probably won't mind if you take his coat, you are cold.", deadGuyRoomItems, 0, 7, 0));
		addRoom(Room("Empty Room", "There are more desks with strange looking equipment.\nYou wonder what the equipment could be for.", vector<Item>(), 0, 8, 0));
		addRoom(Room("Laptop Room", "A single conference table takes up much of this room.", laptopRoomItems, 1, 8, 0));
		addRoom(Room("Hallway 3", "You find yourself in a hallway.\nThere are two doors.", vector<Item>(), 0, 3, 0));
		addRoom(Room("Knife Room", "You find yourself in a hallway.\nHoles have been stabbed in the wall, probably out of frustration.", knifeRoomItems, 0, 2, 0));
		addRoom(Room("HDMI Room", "This room has a desk with a desktop computer on it.\n The computer and the monitor seem to be broken.", hdmiRoomItems, 1, 2, 0));
		addRoom(Room("Flash Drive Room", "There is a nameplate on the desk in this room that says PRESIDENT S. DEVLIN.\nThe word DEVIL is written in blood on the wall behind the desk.\nIn the desk you found a flash drive.", flashDriveRoomItems, 0, 1, 0));
		mutualRoute(rooms[0][4][0], rooms[0][5][0]);
		mutualRoute(rooms[0][5][0], rooms[1][5][0]);
		mutualRoute(rooms[1][6][0], rooms[1][5][0]);
		mutualRoute(rooms[1][6][0], rooms[1][7][0]);
		mutualRoute(rooms[1][8][0], rooms[1][7][0]);
		mutualRoute(rooms[0][7][0], rooms[1][7][0]);
		mutualRoute(rooms[1][8][0], rooms[0][8][0]);
		mutualRoute(rooms[0][7][0], rooms[0][8][0]);
		mutualRoute(rooms[0][4][0], rooms[0][3][0]);
		mutualRoute(rooms[0][2][0], rooms[0][3][0]);
		mutualRoute(rooms[0][2][0], rooms[0][1][0]);
		mutualRoute(rooms[0][2][0], rooms[1][2][0]);
	}
	~Lab() {}

	void success(int itemId)
	{
		switch (itemId)
		{
		case 1:
			cout << "Success! You unlocked this door and escaped!" << endl;
			win = true;
			break;
		case 3:
			cout << "You find a text file on the flash drive.\nIt contains the characters HHCGA." << endl;
			break;
		}
	}
};