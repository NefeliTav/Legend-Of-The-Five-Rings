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
        cout << "Cost: " << cost << endl;

        if (isTapped)
            cout << "  Tapped" << endl;
        else
            cout << "  Not Tapped" << endl;
    }
    int getIsTapped()
    {
        return isTapped;
    }
    int getCost()
    {
        return cost;
    }
    string getName()
    {
        return name;
    }
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
    virtual int getSubType() = 0;
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
    int getisRevealed()
    {
        return isReleaved;
    }
};

#endif