#pragma once

#include "Item.h"
#include <vector>
#include <string>

using namespace std;

class Room
{
private:
    string name, description;
    int x, y, z;
    vector<Item> items;

public:
    Room() {}
    ~Room() {}
    Room(string n, string d, vector<Item> it, int xpos, int ypos, int zpos)
    {
        setName(n);
        setDescription(d);
        setItems(it);
        x = xpos;
        y = ypos;
        z = zpos;
    }

    string getName() { return name; }
    string getDescription() { return description; }
    vector<Item> getItems() { return items; }
    int getX() { return x; }
    int getY() { return y; }
    int getZ() { return z; }

    void setName(string n) { name = n; }
    void setDescription(string d) { description = d; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setZ(int newZ) { z = newZ; }
    void setItems(vector<Item> it) { items = it; }
    void AddItem(Item add) { items.push_back(add); }
    void deleteItem(int deletedId)
    {
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getId() == deletedId)
            {
                items.erase(i);
                break;
            }
        }
    }

    bool hasItem(int itemId)
    {
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getId() == itemId)
                return true;
        }
        return false;
    }

    bool hasAcquirable()
    {
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getAcquirable())
            {
                return true;
            }
        }
        return false;
    }

    vector<Item> acquirables()
    {
        vector<Item> ac;
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getAcquirable())
            {
                ac.push_back(*i);
            }
        }
        return ac;
    }

    bool hasUsable() 
    {
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getUsableInRoom())
            {
                return true;
            }
        }
        return false;
    }

    vector<Item> usables()
    {
        vector<Item> u;
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getUsableInRoom())
            {
                u.push_back(*i);
            }
        }
        return u;
    }

    friend bool operator == (const Room x, const Room y)
    {
        if (x.x == y.x && x.y == y.y)
            return true;
        else
            return false;
    }

    bool hasItem()
    {
        if (items.size() == 0)
            return false;
        else
            return true;
    }

    Item idSearch(int idCheck)
    {
        vector<Item>::iterator i;
        for (i = items.begin(); i != items.end(); ++i)
        {
            if ((*i).getId() == idCheck)
                return (*i);
        }
        return Item();
    }

    string toString()
    {
        string s = description + "\n";
        if (items.size() != 0)
        {
            s += "In this room are the following items:\n";
            for (unsigned int i = 0; i < items.size(); i++)
            {
                s += items[i].getName();
                s += "\n";
            }
        }
        return s;
    }
};