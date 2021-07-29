#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include "Card.hpp"

class Follower : public GreenCard{
    public:
        Follower(string n,int x);
        int getType();
        int getHarvestValue() {
            return 0;
        }
        void printSpecific() {}
};

class Footsoldier : public Follower{
    public:
        Footsoldier(string n,int x);
        int getSubType();
};

class Archer : public Follower{
    public:
        Archer(string n,int x);
        int getSubType();
};

class Cavalry : public Follower{
    public:
        Cavalry(string n,int x);
        int getSubType();
};

class Bushido : public Follower{
    public:
        Bushido(string n,int x);
        int getSubType();
};

class Sieger : public Follower{
    public:
        Sieger(string n,int x);
        int getSubType();
};

class Atakebune : public Follower{
    public:
        Atakebune(string n,int x);
        int getSubType();
};

#endif