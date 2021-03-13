#pragma once
#include <string>

using namespace std;

class Item
{
private:
    string name, description;
    int id, defense;
    bool equippable, isArmor, acquirable, usableInRoom;

public:
    Item() {}
    ~Item() {}
    Item(string n, string d, int idNum, int def, bool e, bool a, bool ac = true, bool uir = false)
    {
        setName(n);
        setDescription(d);
        setId(idNum);
        setDef(def);
        equippable = e;
        isArmor = a;
        acquirable = ac;
        usableInRoom = uir;
    }
   

    string getName() { return name; }
    string getDescription() { return description; }
    int getId() { return id; }
    bool getEquippable() { return equippable; }
    bool getIsArmor() { return isArmor; }
    bool getAcquirable() { return acquirable; }
    bool getUsableInRoom() { return usableInRoom; }
    int getDef() { return defense; }

    void setName(string n) { name = n; }
    void setDescription(string d) { description = d; }
    void setId(int idNum) { id = idNum; }
    void setDef(int def) { defense = def; }

    void clean()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool useItem(bool correctRoom = false, bool otherItem = false)
    {
        switch (getId())
        {
        case 1:
            return keypad1();
            break;
        case 3:
            return laptop(correctRoom, otherItem);
            break;
        }
        
    }

    bool keypad1()
    {
        int input;
        while (true)
        {
            cout << "Enter the code: ";
            if (cin >> input)
                break;
            cout << "Enter a positive integer." << endl;
            clean();
        }
        clean();
        if (input == 88371)
            return true;
        else
            return false;
    }

    float ReturnWeaponDamage() { return 10; }

    bool laptop(bool correctRoom, bool otherItem)
    {
        return (correctRoom && otherItem);
    }
};

class Weapon : public Item
{
private:
    float weaponDamage = 0;
public:
    Weapon(string n, string d, int idNum, float weapDamage) : Item(n, d, idNum, 0, true, false, true, false)
    {
        SetWeaponDamage(weapDamage);
    }
    virtual ~Weapon() = default;

    virtual void SetWeaponDamage(float weapDamage) {weaponDamage = weapDamage;}
    float ReturnWeaponDamage() const { return weaponDamage; }
};

class Crossbow : public Weapon
{
public:
    Crossbow() : Weapon("Crossbow", "A ranged weapon dropped by an enemy.", 20, 10) {}
};

class Pistol : public Weapon
{
public:
    Pistol() : Weapon("Pistol", "A handgun made for close range combat.", 21, 20) {}
};