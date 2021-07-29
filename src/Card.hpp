#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>

using namespace std;

class Card
{
private:
    string name;
    int cost;
    int isTapped; //1 == tapped
public:
    Card(string n, int x);
    void print()
    {
        cout << "Name: " << name << endl;
        if (cost >= 0) //set cost to -1 when bought
            cout << "  Cost: " << cost << endl;
        else
            printSpecific();
        if (isTapped)
            cout << "  Tapped" << endl;
        else
            cout << "  Not Tapped" << endl;
    }
    int getIsTapped()
    {
        return isTapped;
    }
    void setIsTapped(int num)
    {
        if (num < 0 || num > 1)
            isTapped = 1 - isTapped;
        else
            isTapped = num;
    }
    int getCost()
    {
        return cost;
    }
    void setCost()
    {
        cost = -1;
    }
    string getName()
    {
        return name;
    }
    virtual int getHarvestValue() = 0;
    virtual void printSpecific() = 0;
};

class GreenCard : public Card
{
private:
    int attackBonus;
    int defenceBonus;
    int minimumHonour;
    string cardText;
    int effectBonus;
    int effectCost;

public:
    GreenCard(string n, int x);
    virtual int getType() = 0;
    void print()
    {
        Card::print();
        cout << "\tAttack Bonus: " << attackBonus << endl;
        cout << "\tDefence Bonus: " << defenceBonus << endl;
        cout << "\tMinimum Honour: " << minimumHonour << endl;
        cout << "\tText: " << cardText << endl;
        cout << "\tEffect Bonus: " << effectBonus << endl;
        cout << "\tEffect Cost: " << effectCost << endl;
    }
    int getMinimumHonour()
    {
        return minimumHonour;
    }
    int getAB()
    {
        return attackBonus;
    }

    int getDB()
    {
        return defenceBonus;
    }
};

class BlackCard : public Card
{
private:
    int isReleaved;

public:
    BlackCard(string n, int x);
    virtual int getType() = 0;
    virtual int getSubType() = 0;
    void print()
    {
        Card::print();
        if (isReleaved)
            cout << "\tRevealed" << endl;
        else
            cout << "\tNot Revealed" << endl;
    }
    void setIsReleaved(int num)
    {
        if (num < 0 || num > 1)
            return;
        isReleaved = num;
    }
    virtual int getMoney() = 0;
    virtual bool addFollower(GreenCard *) = 0;
    virtual bool addItem(GreenCard *) = 0;
    virtual bool hasUpper() = 0;
    virtual bool hasSub() = 0;
    virtual bool setUpper(BlackCard *holding) = 0;
    virtual bool setSub(BlackCard *holding) = 0;
    virtual bool checkValue() = 0;
    virtual int getPower(bool) = 0;
};

#endif