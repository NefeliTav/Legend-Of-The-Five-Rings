#ifndef _DECKBUILDER_HPP_
#define _DECKBUILDER_HPP_

//Personalities:
enum{ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};
//Holdings:
enum{PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};
//Followers:
enum{FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};
//Items:
enum{KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <ctime>
#include <cstdlib>

#include "Card.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Item.hpp"

#define DECKSIZE          40
#define MAXDECKSIZE       60

#define NO_PERSONALITIES  25
#define NO_DEFENSIVE      10
#define NO_ATTACKING      10
#define NO_SHOGUN         2
#define NO_CHANCELLOR     2
#define NO_CHAMPION       1

#define NO_HOLDINGS       17
#define NO_PLAIN          3
#define NO_MINE           3
#define NO_GOLD_MINE      3
#define NO_CRYSTAL_MINE   3
#define NO_FARMS          3
#define NO_SOLO           2

#define NO_FOLLOWERS      28
#define NO_FOOTSOLDIER    6
#define NO_ARCHER         6
#define NO_SIEGER         4
#define NO_CAVALRY        5
#define NO_NAVAL          5
#define NO_BUSHIDO        2

#define NO_ITEMS          12
#define NO_KATANA         4
#define NO_SPEAR          3
#define NO_BOW            2
#define NO_NINJATO        2
#define NO_WAKIZASHI      1

class DeckBuilder {
	private:
		list<GreenCard*>* green;
		list<BlackCard*>* black;
	public:
		DeckBuilder();
		~DeckBuilder();
		list<GreenCard *>* createFateDeck();
	 	list<BlackCard *>* createDynastyDeck();

	 	void deckShuffler(list<BlackCard *> *black);
		void deckShuffler(list<GreenCard *> *green);

		GreenCard* getFrontGreen() {
			return green->front();
		}

		BlackCard* getFrontBlack() {
			return black->front();
		}

		void popFrontGreen() {
            green->pop_front();
		}

		void popFrontBlack() {
            black->pop_front();
		}
};

#endif