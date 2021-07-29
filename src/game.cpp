#include <iostream>
using namespace std;

#include "DeckBuilder.hpp"
#include "TypeConverter.hpp"
#include <time.h>

#define MAX_CARD_IN_HAND 7
#define STARTING_HAND_NUM 4

class Player
{
private:
    int pl;
    DeckBuilder *d; // fatedeck & dynastydeck
    list<GreenCard *> *hand;
    list<BlackCard *> *provinces; //4 at first,isrevealed = 0
    list<BlackCard *> *army;      //empty at first
    list<BlackCard *> *h;         //empty at first
    Stronghold *s;
    int numberOfProvinces;

public:
    Player(int num)
    {
        pl = num;
        //cout << "create player\n";
        d = new DeckBuilder();
        s = new Stronghold("my stronghold", STRONGHOLD);
        provinces = new list<BlackCard *>();
        hand = new list<GreenCard *>();
        for (int i = 0; i < STARTING_HAND_NUM; i++)
            getGreen();
        for (int i = 0; i < 4; i++)
            getBlack();
        h = new list<BlackCard *>();
        army = new list<BlackCard *>();
        h->push_front(s);
    }
    ~Player()
    {
        //cout << "delete player\n";
        delete s;
        delete d;
    }
    void getGreen()
    {
        hand->push_front(d->getFrontGreen());
        d->popFrontGreen();
    }
    void getBlack()
    {
        provinces->push_front(d->getFrontBlack());
        d->popFrontBlack();
    }
    int get_honor()
    {
        return s->honor();
    }

    int get_army()
    {
        return army->empty();
    }
};

int get_cost(int);

Card::Card(string n, int x)
{
    name = n;
    cost = get_cost(x);
    isTapped = 0;
}

GreenCard::GreenCard(string n, int x) : Card(n, x)
{
    if (x == FOOTSOLDIER)
    {
        attackBonus = 2;
        defenceBonus = 0;
        minimumHonour = 1;
        effectBonus = 1;
        effectCost = 2;
    }
    else if (x == ARCHER)
    {
        attackBonus = 0;
        defenceBonus = 2;
        minimumHonour = 1;
        effectBonus = 1;
        effectCost = 2;
    }
    else if (x == SIEGER)
    {
        attackBonus = 3;
        defenceBonus = 3;
        minimumHonour = 2;
        effectBonus = 2;
        effectCost = 3;
    }
    else if (x == CAVALRY)
    {
        attackBonus = 4;
        defenceBonus = 2;
        minimumHonour = 3;
        effectBonus = 3;
        effectCost = 4;
    }
    else if (x == NAVAL)
    {
        attackBonus = 2;
        defenceBonus = 4;
        minimumHonour = 3;
        effectBonus = 3;
        effectCost = 4;
    }
    else if (x == BUSHIDO)
    {
        attackBonus = 8;
        defenceBonus = 8;
        minimumHonour = 6;
        effectBonus = 3;
        effectCost = 8;
    }
    else if (x == KATANA)
    {
        attackBonus = 2;
        defenceBonus = 0;
        minimumHonour = 1;
        effectBonus = 1;
        effectCost = 2;
    }
    else if (x == SPEAR)
    {
        attackBonus = 0;
        defenceBonus = 2;
        minimumHonour = 1;
        effectBonus = 1;
        effectCost = 2;
    }
    else if (x == BOW)
    {
        attackBonus = 2;
        defenceBonus = 2;
        minimumHonour = 2;
        effectBonus = 3;
        effectCost = 4;
    }
    else if (x == NINJATO)
    {
        attackBonus = 3;
        defenceBonus = 3;
        minimumHonour = 3;
        effectBonus = 2;
        effectCost = 2;
    }
    else if (x == WAKIZASHI)
    {
        attackBonus = 5;
        defenceBonus = 5;
        minimumHonour = 3;
        effectBonus = 3;
        effectCost = 3;
    }
}

BlackCard::BlackCard(string n, int x) : Card(n, x)
{
    isReleaved = 0;
}
Follower::Follower(string n, int x) : GreenCard(n, x) {}
Item::Item(string n, int x) : GreenCard(n, x)
{
    if (x == KATANA)
    {
        durability = 3;
    }
    else if (x == SPEAR)
    {
        durability = 3;
    }
    else if (x == BOW)
    {
        durability = 5;
    }
    else if (x == NINJATO)
    {
        durability = 4;
    }
    else if (x == WAKIZASHI)
    {
        durability = 8;
    }
}

Personality::Personality(string n, int x) : BlackCard(n, x)
{
    if (x == ATTACKER)
    {
        attack = 3;
        defence = 2;
        honour = 2;
        maxFollowers = 0;
        maxItems = 2;
    }
    else if (x == DEFENDER)
    {
        attack = 2;
        defence = 3;
        honour = 2;
        maxFollowers = 0;
        maxItems = 2;
    }
    else if (x == SHOGUN)
    {
        attack = 10;
        defence = 5;
        honour = 8;
        maxFollowers = 2;
        maxItems = 2;
    }
    else if (x == CHANCELLOR)
    {
        attack = 5;
        defence = 10;
        honour = 8;
        maxFollowers = 3;
        maxItems = 1;
    }
    else if (x == CHAMPION)
    {
        attack = 20;
        defence = 20;
        honour = 12;
        maxFollowers = 1;
        maxItems = 3;
    }
    isDead = 0;
    followers = new list<GreenCard *>();
    items = new list<GreenCard *>();
}

Holding::Holding(string n, int x) : BlackCard(n, x)
{
    if (x == SOLO)
        harvestValue = 2;
    else if (x == PLAIN)
        harvestValue = 2;
    else if (x == FARMS)
        harvestValue = 4;
    else if (x == MINE)
        harvestValue = 3;
    else if (x == GOLD_MINE)
        harvestValue = 5;
    else if (x == CRYSTAL_MINE)
        harvestValue = 6;
    else if (x == STRONGHOLD)
        harvestValue = 5;

    bonusValue = 0;
    upperHolding = NULL;
    subHolding = NULL;
}

Stronghold::Stronghold(string n, int x) : Holding(n, x)
{
    startinghonour = 5;
    initialDefense = 5;
}

Katana::Katana(string n, int x) : Item(n, x) {}
Spear::Spear(string n, int x) : Item(n, x) {}
Bow::Bow(string n, int x) : Item(n, x) {}
Ninjato::Ninjato(string n, int x) : Item(n, x) {}
Wakizashi::Wakizashi(string n, int x) : Item(n, x) {}
Footsoldier::Footsoldier(string n, int x) : Follower(n, x) {}
Archer::Archer(string n, int x) : Follower(n, x) {}
Cavalry::Cavalry(string n, int x) : Follower(n, x) {}
Bushido::Bushido(string n, int x) : Follower(n, x) {}
Sieger::Sieger(string n, int x) : Follower(n, x) {}
Atakebune::Atakebune(string n, int x) : Follower(n, x) {}
Attacker::Attacker(string n, int x) : Personality(n, x) {}
Defender::Defender(string n, int x) : Personality(n, x) {}
Champion::Champion(string n, int x) : Personality(n, x) {}
Chancellor::Chancellor(string n, int x) : Personality(n, x) {}
Shogun::Shogun(string n, int x) : Personality(n, x) {}
Plain::Plain(string n, int x) : Holding(n, x) {}
Mine::Mine(string n, int x) : Holding(n, x) {}
GoldMine::GoldMine(string n, int x) : Holding(n, x) {}
CrystalMine::CrystalMine(string n, int x) : Holding(n, x) {}
Farmland::Farmland(string n, int x) : Holding(n, x) {}
GiftsandFavour::GiftsandFavour(string n, int x) : Holding(n, x) {}

//get type to get this
int Holding::getType() { return HOLDING; }
int Follower::getType() { return FOLLOWER; }
int Personality::getType() { return PERSONALITY; }
int Item::getType() { return ITEM; }

//get subtype to get what type of that
int Attacker::getSubType() { return ATTACKER; }
int Defender::getSubType() { return DEFENDER; }
int Champion::getSubType() { return CHAMPION; }
int Chancellor::getSubType() { return CHANCELLOR; }
int Shogun::getSubType() { return SHOGUN; }

int Footsoldier::getSubType() { return FOOTSOLDIER; }
int Archer::getSubType() { return ARCHER; }
int Cavalry::getSubType() { return CAVALRY; }
int Bushido::getSubType() { return BUSHIDO; }
int Sieger::getSubType() { return SIEGER; }
int Atakebune::getSubType() { return NAVAL; }

int Plain::getSubType() { return PLAIN; }
int Mine::getSubType() { return MINE; }
int GoldMine::getSubType() { return GOLD_MINE; }
int CrystalMine::getSubType() { return CRYSTAL_MINE; }
int Farmland::getSubType() { return FARMS; }
int GiftsandFavour::getSubType() { return SOLO; }
int Stronghold::getSubType() { return STRONGHOLD; }

int Katana::getSubType() { return KATANA; }
int Spear::getSubType() { return SPEAR; }
int Bow::getSubType() { return BOW; }
int Ninjato::getSubType() { return NINJATO; }
int Wakizashi::getSubType() { return WAKIZASHI; }

int get_cost(int x)
{
    int cost;
    if (x == FOOTSOLDIER)
        cost = 0;
    else if (x == ARCHER)
        cost = 0;
    else if (x == SIEGER)
        cost = 5;
    else if (x == CAVALRY)
        cost = 3;
    else if (x == NAVAL)
        cost = 3;
    else if (x == BUSHIDO)
        cost = 8;
    else if (x == KATANA)
        cost = 0;
    else if (x == SPEAR)
        cost = 0;
    else if (x == BOW)
        cost = 2;
    else if (x == NINJATO)
        cost = 4;
    else if (x == WAKIZASHI)
        cost = 8;
    else if (x == ATTACKER)
        cost = 5;
    else if (x == DEFENDER)
        cost = 5;
    else if (x == SHOGUN)
        cost = 15;
    else if (x == CHANCELLOR)
        cost = 15;
    else if (x == CHAMPION)
        cost = 30;
    else if (x == SOLO)
        cost = 2;
    else if (x == PLAIN)
        cost = 2;
    else if (x == FARMS)
        cost = 3;
    else if (x == MINE)
        cost = 5;
    else if (x == GOLD_MINE)
        cost = 7;
    else if (x == CRYSTAL_MINE)
        cost = 12;
    else
        return -1;
    return cost;
}
