#ifndef ITEM_HPP
#define ITEM_HPP

#include "Card.hpp"

class Item : public GreenCard
{
private:
    int durability;

public:
    Item(string n, int x);
    int getType();
    int getHarvestValue()
    {
        return 0;
    }
    void printSpecific()
    {
        cout << "\t  Durability: " << durability << endl;
    }
};

class Katana : public Item
{
public:
    Katana(string n, int x);
    int getSubType();
};

class Spear : public Item
{
public:
    Spear(string n, int x);
    int getSubType();
};

class Bow : public Item
{
public:
    Bow(string n, int x);
    int getSubType();
};

class Ninjato : public Item
{
public:
    Ninjato(string n, int x);
    int getSubType();
};

class Wakizashi : public Item
{
public:
    Wakizashi(string n, int x);
    int getSubType();
};

#endif