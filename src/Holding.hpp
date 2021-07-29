#ifndef HOLDING_HPP
#define HOLDING_HPP

#include "Card.hpp"
#include "DeckBuilder.hpp"

class Holding : public BlackCard
{

private:
    int harvestValue;
    int bonusValue;
    BlackCard *upperHolding;
    BlackCard *subHolding;

public:
    Holding(string n, int x);
    int getType();
    int getMoney()
    {
        return harvestValue + bonusValue;
    }
    int getHarvestValue()
    {
        return harvestValue + bonusValue;
    }
    void setHarvestValue(int num)
    {
        if (num < 0)
            return;
        harvestValue = num;
    }
    void printSpecific()
    {
        cout << "\t  Harvest Value: " << harvestValue << endl;
        if (upperHolding != NULL)
            cout << "\t  Upper Holding: " << upperHolding->Card::getName() << endl;
        if (subHolding != NULL)
            cout << "\t  Sub Holding: " << subHolding->Card::getName() << endl;
    }
    bool addFollower(GreenCard *follower) { return false; }
    bool addItem(GreenCard *item) { return false; }
    bool hasUpper()
    {
        if (upperHolding == NULL)
            return false;
        return true;
    }
    bool hasSub()
    {
        if (subHolding == NULL)
            return false;
        return true;
    }
    bool setUpper(BlackCard *holding)
    {
        upperHolding = holding;
        return true;
    }
    bool setSub(BlackCard *holding)
    {
        subHolding = holding;
        return true;
    }
    bool checkValue()
    {
        if (!hasSub() && !hasUpper())
            return true;
        if (getSubType() == MINE && hasUpper() && upperHolding->getSubType() == GOLD_MINE)
            bonusValue = 2;
        else if (getSubType() == GOLD_MINE && hasSub() && subHolding->getSubType() == MINE)
            bonusValue = 4;
        else if (getSubType() == GOLD_MINE && hasUpper() && upperHolding->getSubType() == CRYSTAL_MINE && !hasSub())
            bonusValue = 5;
        else if (getSubType() == GOLD_MINE && hasUpper() && upperHolding->getSubType() == CRYSTAL_MINE && hasSub() && subHolding->getSubType() == MINE)
            bonusValue = 2 * harvestValue;
        else if (getSubType() == CRYSTAL_MINE && hasSub() && subHolding->getSubType() == GOLD_MINE && !subHolding->hasSub())
            bonusValue = harvestValue;
        else if (getSubType() == CRYSTAL_MINE && hasSub() && subHolding->getSubType() == GOLD_MINE && subHolding->hasSub())
            bonusValue = 3 * harvestValue;
        return true;
    }
    int getPower(bool isAttack) { return 0; }
};

class Plain : public Holding
{
public:
    Plain(string n, int x);
    int getSubType();
};

class Mine : public Holding
{
public:
    Mine(string n, int x);
    int getSubType();
};

class GoldMine : public Holding
{
public:
    GoldMine(string n, int x);
    int getSubType();
};

class CrystalMine : public Holding
{
public:
    CrystalMine(string n, int x);
    int getSubType();
};
class Farmland : public Holding
{
public:
    Farmland(string n, int x);
    int getSubType();
};

class GiftsandFavour : public Holding
{
public:
    GiftsandFavour(string n, int x);
    int getSubType();
};

class Stronghold : public Holding
{
private:
    int startinghonour;
    int money;
    int initialDefense;

public:
    Stronghold(string n, int x);
    int getSubType();
    int honor()
    {
        return startinghonour;
    }
};

#endif
