#ifndef PERSONALITY_HPP
#define PERSONALITY_HPP

#include "Card.hpp"
#include "Follower.hpp"
#include "Item.hpp"
#include <list>

class Personality : public BlackCard
{
private:
    int attack;
    int defence;
    int honour;
    int isDead;
    int maxFollowers;
    int maxItems;
    list<GreenCard *> *followers;
    list<GreenCard *> *items;

public:
    Personality(string n, int x);
    int getType();
    int getMoney()
    {
        return 0;
    }
    int getHarvestValue()
    {
        return 0;
    }
    void printSpecific()
    {
        cout << "\t  Attack: " << getPower(true) << endl;
        cout << "\t  Defence: " << getPower(false) << endl;
        cout << "\t  Honour: " << honour << endl;
        if (isDead)
            cout << "\t  Dead" << endl;
        else
            cout << "\t  Alive" << endl;
        //print for followers and items
    }
    bool isFollowersFull()
    {
        if (followers->size() < maxFollowers)
            return false;
        return true;
    }
    bool isItemsFull()
    {
        if (followers->size() < maxItems)
            return false;
        return true;
    }
    bool addFollower(GreenCard *follower)
    {
        if (isFollowersFull())
        {
            cout << "- " << getName() << " - already has enough followers" << endl;
            return false;
        }
        if (follower->getMinimumHonour() > honour)
        {
            cout << "- " << getName() << " - does not satisfy the honour requirements" << endl;
            return false;
        }
        followers->push_back(follower);
        return true;
    }
    bool addItem(GreenCard *item)
    {
        if (isItemsFull())
        {
            cout << "- " << getName() << " - already has enough items" << endl;
            return false;
        }
        if (item->getMinimumHonour() > honour)
        {
            cout << "- " << getName() << " - does not satisfy the honour requirements" << endl;
            return false;
        }
        items->push_back(item);
        return true;
    }
    int getPower(bool isAttack)
    {
        int sum;
        if (isAttack)
        {
            sum = attack;
            if (followers && !followers->empty())
            {
                for (list<GreenCard *>::iterator it = followers->begin(); it != followers->end(); ++it)
                {
                    sum += (*it)->getAB();
                }
            }
            if (items && !items->empty())
            {
                for (list<GreenCard *>::iterator it = items->begin(); it != items->end(); ++it)
                {
                    sum += (*it)->getAB();
                }
            }
        }
        else
        {
            sum = defence;
            if (followers && !followers->empty())
            {
                for (list<GreenCard *>::iterator it = followers->begin(); it != followers->end(); ++it)
                {
                    sum += (*it)->getDB();
                }
            }
            if (items && !items->empty())
            {
                for (list<GreenCard *>::iterator it = items->begin(); it != items->end(); ++it)
                {
                    sum += (*it)->getDB();
                }
            }
        }
        return sum;
    }
    bool hasUpper() { return true; }
    bool hasSub() { return true; }
    bool setUpper(BlackCard *holding) { return false; }
    bool setSub(BlackCard *holding) { return false; }
    bool checkValue() { return false; }
};

class Attacker : public Personality
{
public:
    Attacker(string n, int x);
    int getSubType();
};
class Defender : public Personality
{
public:
    Defender(string n, int x);
    int getSubType();
};
class Champion : public Personality
{
public:
    Champion(string n, int x);
    int getSubType();
};
class Chancellor : public Personality
{
public:
    Chancellor(string n, int x);
    int getSubType();
};
class Shogun : public Personality
{
public:
    Shogun(string n, int x);
    int getSubType();
};

#endif