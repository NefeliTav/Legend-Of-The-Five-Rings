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