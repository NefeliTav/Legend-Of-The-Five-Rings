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
    DeckBuilder *d;
    list<GreenCard *> *hand;
    list<BlackCard *> *provinces; //4 in the beginning
    list<BlackCard *> *army;      //empty in the beginning
    list<BlackCard *> *h;         //empty in the beginning
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

    int calculateMoney()
    {
        int money = 0;
        list<BlackCard *>::iterator it;
        if (h == NULL || h->empty())
            return 0;
        for (it = h->begin(); it != h->end(); ++it)
        {
            money += (*it)->getMoney();
        }
        return money;
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
    void untapEverything()
    {
        if (h == NULL || h->empty())
            return;
        list<BlackCard *>::iterator it;
        for (it = h->begin(); it != h->end(); ++it)
        {
            (*it)->setIsTapped(0);
        }
    }
    void drawFateCard()
    {
        getGreen();
    }
    void revealProvinces()
    {
        if (provinces == NULL || provinces->empty())
            return;
        list<BlackCard *>::iterator it;
        for (it = provinces->begin(); it != provinces->end(); ++it)
        {
            (*it)->setIsReleaved(1);
        }
    }
    void printHand(bool showNum = false)
    { //show the number so player can choose and buy
        list<GreenCard *>::iterator it;
        cout << "Hand:" << endl;
        cout << "=============" << endl;
        if (hand == NULL || hand->empty())
            return;
        int i = 0;
        for (it = hand->begin(); it != hand->end(); ++it)
        {
            if (showNum)
                cout << i << ")" << endl;
            (*it)->print();
            i++;
        }
    }
    void printProvinces(bool showNum = false)
    { //show the number so player can choose and buy
        list<BlackCard *>::iterator it;
        cout << "Provinces:" << endl;
        cout << "=============" << endl;
        if (provinces == NULL || provinces->empty())
            return;
        int i = 0;
        for (it = provinces->begin(); it != provinces->end(); ++it)
        {
            if (showNum)
                cout << i << ")" << endl;

            (*it)->print();
            i++;
        }
    }

    void printArmy(bool showNum = false)
    { //show the number so player can choose and buy
        list<BlackCard *>::iterator it;
        cout << "Army:" << endl;
        cout << "=============" << endl;
        if (army == NULL || army->empty())
            return;
        int i = 0;
        for (it = army->begin(); it != army->end(); ++it)
        {
            if (showNum)
                cout << i << ")" << endl;
            (*it)->print();
            i++;
        }
    }

    void printHoldings(bool showNum = false)
    { //show the number so player can choose and buy
        list<BlackCard *>::iterator it;
        cout << "Holdings:" << endl;
        cout << "=============" << endl;
        if (h == NULL || h->empty())
            return;
        int i = 0;
        for (it = h->begin(); it != h->end(); ++it)
        {
            if (showNum)
                cout << i << ")" << endl;
            (*it)->print();
            i++;
        }
    }

    void startingPhase()
    {
        cout << endl
             << " __  _____   __    ___  _____  _   _      __        ___   _      __    __   ____" << endl;
        cout << "( (`  | |   / /\\  | |_)  | |  | | | |\\ | / /`_     | |_) | |_|  / /\\  ( (` | |_  " << endl;
        cout << "_)_)  |_|  /_/--\\ |_| \\  |_|  |_| |_| \\| \\_\\_/     |_|   |_| | /_/--\\ _)_) |_|__ \t( Player: " << pl << " )" << endl
             << endl;
        untapEverything();
        drawFateCard();
        revealProvinces();
        printHand(false);
        printProvinces(false);
    }
    void equipPhase()
    {
        cout << endl
             << " ____  ___    _     _   ___       ___   _      __    __   ____ " << endl;
        cout << "| |_  / / \\  | | | | | | |_)     | |_) | |_|  / /\\  ( (` | |_ " << endl;
        cout << "|_|__ \\_\\_\\\\ \\_\\_/ |_| |_|       |_|   |_| | /_/--\\ _)_) |_|__\t( Player: " << pl << " )" << endl
             << endl;

        if (army->empty())
        {
            cin.clear();
            cout << "You have no army so you cannot buy..." << endl;
            getchar();
            return;
        }
        int cardNum, i;
        list<int> toRemove;
        list<GreenCard *>::iterator it;
        list<BlackCard *>::iterator it2;
        GreenCard *wantToBuy;

        printHand(true);
        printProvinces(false);
        cout << "- Money available: " << calculateMoney() << " -" << endl;
        if (hand->empty())
        {
            cout << "Hand is empty..." << endl;
            getchar();
            return;
        }
        /////////////////////////////
        cardNum = -2;
        //choose a card from your hand to buy
        while (cardNum != -1 && hand->size() != 0 && !army->empty())
        {
            cout << "Select card (0 - " << hand->size() - 1 << ") or -1 to continue:" << endl;
            cin.clear(); //so that it waits for new cin
            cin >> cardNum;
            if (cardNum < -1 || cardNum >= hand->size())
                cout << "No such card..." << endl;
            else
            {
                i = 0;
                for (it = hand->begin(); it != hand->end(); ++it)
                {
                    if (i == cardNum)
                        break;
                    i++;
                }
                wantToBuy = *it;
                if ((*it)->getCost() > calculateMoney())
                {
                    cout << "Not enough money" << endl;
                }
                else
                {
                    // if you can buy it
                    int money = (*it)->getCost();
                    printHoldings(true);
                    cardNum = -2;
                    //choose the cards you want to tap to buy it
                    while (money > 0 && cardNum != -1 && h->size() != 0)
                    {
                        cout << "Choose a card to Tap to reach " << money << " coins or -1 to exit:" << endl;
                        cin.clear();
                        cin >> cardNum;
                        if (cardNum < -1 || cardNum >= h->size())
                            cout << "No such card..." << endl;
                        else if (contains(toRemove, i))
                        {
                            cout << "Already selected..." << endl;
                        }
                        else
                        {
                            i = 0;
                            for (it2 = h->begin(); it2 != h->end(); ++it2)
                            {
                                if (i == cardNum)
                                    break;
                                i++;
                            }
                            if ((*it2)->getIsTapped())
                            {
                                cout << "Card already tapped..." << endl;
                            }
                            else
                            {
                                money -= (*it2)->getHarvestValue();
                                toRemove.push_front(i);
                            }
                        }
                    }
                    //if you ve tapped enough cards to buy the wantToBuy card
                    if (cardNum != -1)
                    {
                        cardNum = -2;
                        while (cardNum != -1 && !army->empty())
                        {
                            printArmy(true);
                            cout << "Select card (0 - " << army->size() - 1 << ") to equip - " << wantToBuy->getName() << " - to or -1 to continue:" << endl;
                            cin.clear(); //so that it waits for new cin
                            cin >> cardNum;
                            if (cardNum < -1 || cardNum >= army->size())
                                cout << "No such card..." << endl;
                            else
                            {
                                i = 0;
                                for (it2 = army->begin(); it2 != army->end(); ++it2)
                                {
                                    if (cardNum == i)
                                        break;
                                    i++;
                                }
                                //check max followers and max items
                                if (((wantToBuy->getType() == FOLLOWER) && ((*it2)->addFollower(wantToBuy))) || ((wantToBuy->getType() == ITEM) && ((*it2)->addItem(wantToBuy))))
                                {
                                    //tap the cards selected
                                    i = 0;
                                    if (!toRemove.empty())
                                    {
                                        toRemove.sort();
                                        for (it2 = h->begin(); it2 != h->end(); ++it2)
                                        {
                                            if (toRemove.empty())
                                                break;
                                            if (i == toRemove.front())
                                            {
                                                toRemove.pop_front();
                                                (*it2)->setIsTapped(1);
                                            }
                                            i++;
                                        }
                                    }
                                    wantToBuy->setCost();
                                    //you bought it so remove it from your hand
                                    for (it = hand->begin(); it != hand->end(); ++it)
                                    {
                                        if ((*it) == wantToBuy)
                                        {
                                            hand->erase(it);
                                            break;
                                        }
                                    }
                                    cardNum = -1;
                                }
                                else
                                {
                                    cout << "Please try again..." << endl;
                                }
                            }
                        }
                    }
                    cardNum = -2;
                    //stuff
                    printHand(true);
                }
            }
        }
    }
    /////////////////////////////

    void discardSurplusFateCards()
    {
        int cardNum;
        list<GreenCard *>::iterator it;
        printHand(true);
        cout << "Select card (0 - " << hand->size() - 1 << ") to discard:" << endl;
        cin.clear(); //so that it waits for new cin
        cin >> cardNum;
        if (cardNum < 0 || cardNum >= hand->size())
            cout << "No such card..." << endl;
        else
        {
            int i = 0;
            for (it = hand->begin(); it != hand->end(); ++it)
            {
                if (i == cardNum)
                    break;
                i++;
            }
            hand->erase(it);
        }
    }

    bool contains(list<int> l, int num)
    {
        list<int>::iterator it;
        for (it = l.begin(); it != l.end(); ++it)
        {
            if (*it == num)
                return true;
        }
        return false;
    }

    void economyPhase()
    {
        cout << endl
             << " ____  __    ___   _      ___   _      _         ___   _      __    __   ____" << endl;
        cout << "| |_  / /`  / / \\ | |\\ | / / \\ | |\\/| \\ \\_/     | |_) | |_|  / /\\  ( (` | |_  " << endl;
        cout << "|_|__ \\_\\_, \\_\\_/ |_| \\| \\_\\_/ |_|  |  |_|      |_|   |_| | /_/--\\ _)_) |_|__\t( Player: " << pl << " )" << endl
             << endl;
        int cardNum, i;
        list<int> toRemove;
        list<BlackCard *>::iterator it;
        BlackCard *wantToBuy;
        if (provinces == NULL || provinces->empty())
            return;
        for (it = provinces->begin(); it != provinces->end(); ++it)
        {
            (*it)->setIsReleaved(1);
        }
        printProvinces(true);
        cout << "- Money available: " << calculateMoney() << " -" << endl;
        /////////////////////////////////
        if (provinces->empty())
        {
            cout << "No provinces available..." << endl;
            getchar();
            return;
        }
        cardNum = -2;
        while (cardNum != -1 && provinces->size() != 0)
        {
            cout << "Select card (0 - " << provinces->size() - 1 << ") or -1 to continue:" << endl;
            cin.clear(); //so that it waits for new cin
            cin >> cardNum;
            if (cardNum < -1 || cardNum >= provinces->size())
                cout << "No such card..." << endl;
            else
            {
                //buy card
                i = 0;
                for (it = provinces->begin(); it != provinces->end(); ++it)
                {
                    if (i == cardNum)
                        break;
                    i++;
                }
                wantToBuy = *it;
                if ((*it)->getCost() > calculateMoney())
                {
                    cout << "Not enough money" << endl;
                }
                else
                {
                    int money = (*it)->getCost();
                    printHoldings(true);
                    cardNum = -2;
                    while (money > 0 && cardNum != -1 && h->size() != 0)
                    {
                        cout << "Choose a card to Tap to reach " << money << " coins or -1 to exit:" << endl;
                        cin.clear();
                        cin >> cardNum;
                        if (cardNum < -1 || cardNum >= h->size())
                            cout << "No such card..." << endl;
                        else if (contains(toRemove, i))
                        {
                            cout << "Already selected..." << endl;
                        }
                        else
                        {
                            i = 0;
                            for (it = h->begin(); it != h->end(); ++it)
                            {
                                if (i == cardNum)
                                    break;
                                i++;
                            }
                            if ((*it)->getIsTapped())
                            {
                                cout << "Card already tapped..." << endl;
                            }
                            else
                            {
                                money -= (*it)->getHarvestValue();
                                toRemove.push_front(i);
                            }
                        }
                    }
                    if (cardNum != -1)
                    { //remove the cards selected
                        i = 0;
                        if (!toRemove.empty())
                        {
                            toRemove.sort();
                            for (it = h->begin(); it != h->end(); ++it)
                            {
                                if (toRemove.empty())
                                    break;
                                if (i == toRemove.front())
                                {
                                    toRemove.pop_front();
                                    (*it)->setIsTapped(1);
                                }
                                i++;
                            }
                        }
                        wantToBuy->setCost();
                        if (wantToBuy->getType() == HOLDING)
                        {
                            //check for chain
                            if (wantToBuy->getSubType() == CRYSTAL_MINE)
                            {
                                //search for subholding
                                //search for gold mines first
                                bool found = false;
                                for (it = h->begin(); it != h->end(); ++it)
                                {
                                    if ((*it)->getSubType() == GOLD_MINE && !(*it)->hasUpper())
                                    {
                                        //found subholding
                                        wantToBuy->setSub(*it);
                                        (*it)->setUpper(wantToBuy);
                                        wantToBuy->checkValue();
                                        (*it)->checkValue();
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found)
                                {
                                    //search for mines
                                    for (it = h->begin(); it != h->end(); ++it)
                                    {
                                        if ((*it)->getSubType() == MINE && !(*it)->hasUpper())
                                        {
                                            //found subholding
                                            wantToBuy->setSub(*it);
                                            (*it)->setUpper(wantToBuy);
                                            wantToBuy->checkValue();
                                            (*it)->checkValue();
                                            found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (wantToBuy->getSubType() == MINE)
                            {
                                //search for upperholding
                                bool found = false;
                                //search gold
                                for (it = h->begin(); it != h->end(); ++it)
                                {
                                    if ((*it)->getSubType() == GOLD_MINE && !(*it)->hasSub())
                                    {
                                        //found upperholding
                                        wantToBuy->setUpper(*it);
                                        (*it)->setSub(wantToBuy);
                                        wantToBuy->checkValue();
                                        (*it)->checkValue();
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found)
                                {
                                    //search for crystal
                                    for (it = h->begin(); it != h->end(); ++it)
                                    {
                                        if ((*it)->getSubType() == CRYSTAL_MINE && !(*it)->hasSub())
                                        {
                                            //found upperholding
                                            wantToBuy->setUpper(*it);
                                            (*it)->setSub(wantToBuy);
                                            wantToBuy->checkValue();
                                            (*it)->checkValue();
                                            found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (wantToBuy->getSubType() == GOLD_MINE)
                            {
                                //search for subholding
                                //search for mines
                                for (it = h->begin(); it != h->end(); ++it)
                                {
                                    if ((*it)->getSubType() == MINE && !(*it)->hasUpper())
                                    {
                                        //found subholding
                                        wantToBuy->setSub(*it);
                                        (*it)->setUpper(wantToBuy);
                                        wantToBuy->checkValue();
                                        (*it)->checkValue();
                                        break;
                                    }
                                }
                                //search for upperholding
                                //search for crystal
                                for (it = h->begin(); it != h->end(); ++it)
                                {
                                    if ((*it)->getSubType() == CRYSTAL_MINE && !(*it)->hasSub())
                                    {
                                        //found upperholding
                                        wantToBuy->setUpper(*it);
                                        (*it)->setSub(wantToBuy);
                                        wantToBuy->checkValue();
                                        (*it)->checkValue();
                                        break;
                                    }
                                }
                            }
                            h->push_back(wantToBuy);
                        }
                        else if (wantToBuy->getType() == PERSONALITY)
                        {
                            army->push_back(wantToBuy);
                        }
                        wantToBuy->setIsTapped(1);
                        for (it = provinces->begin(); it != provinces->end(); ++it)
                        {
                            if ((*it) == wantToBuy)
                            {
                                provinces->erase(it);
                                break;
                            }
                        }
                        //stuff
                        printProvinces(true);
                    }
                    cardNum = -2;
                }
            }
        }
        /////////////////////////////////
    }

    int sumAttack()
    {
        list<BlackCard *>::iterator it;
        int sum = 0;
        if (army == NULL || army->empty())
            return 0;
        for (it = army->begin(); it != army->end(); ++it)
        {
            if ((*it)->getIsTapped())
                sum += (*it)->getPower(true);
        }
        return sum;
    }

    int sumDefense()
    {
        list<BlackCard *>::iterator it;
        int sum = 0;
        if (army == NULL || army->empty())
            return 0;
        for (it = army->begin(); it != army->end(); ++it)
        {
            if ((*it)->getIsTapped())
                sum += (*it)->getPower(false);
        }
        return sum;
    }

    void battlePhase()
    {
        cout << endl
             << " ___    __   _____ _____  _     ____      ___   _      __    __   ____" << endl;
        cout << "| |_)  / /\\   | |   | |  | |   | |_      | |_) | |_|  / /\\  ( (` | |_ " << endl;
        cout << "|_|_) /_/--\\  |_|   |_|  |_|__ |_|__     |_|   |_| | /_/--\\ _)_) |_|__\t( Player: " << pl << " )" << endl
             << endl;
        printArmy(true);
        int cardNum = -2;
        list<BlackCard *>::iterator it;
        while (cardNum != -1 && army->size() != 0)
        {
            cout << "Select card (0 - " << army->size() - 1 << ") to tap/untap or -1 to continue:" << endl;
            cin.clear(); //so that it waits for new cin
            cin >> cardNum;
            if (cardNum < -1 || cardNum >= army->size())
                cout << "No such card..." << endl;
            else
            {
                int i = 0;
                for (it = army->begin(); it != army->end(); ++it)
                {
                    if (i == cardNum)
                        break;
                    i++;
                }
                (*it)->setIsTapped(-1);
                printArmy(true);
            }
        }
    }

    void finalPhase()
    {
        cout << endl
             << " ____  _   _       __    _         ___   _      __    __   ____ " << endl;
        cout << "| |_  | | | |\\ |  / /\\  | |       | |_) | |_|  / /\\  ( (` | |_" << endl;
        cout << "|_|   |_| |_| \\| /_/--\\ |_|__     |_|   |_| | /_/--\\ _)_) |_|__ \t( Player: " << pl << " )" << endl
             << endl;
        while (hand->size() > MAX_CARD_IN_HAND)
            discardSurplusFateCards();
        cin.clear();
        //print stuff
    }

    int getName()
    {
        return pl;
    }

    void lost()
    {
        for (list<BlackCard *>::iterator it = army->begin(); it != army->end(); ++it)
        {
            if ((*it)->getIsTapped())
            {
                army->erase(it);
            }
        }
    }

    void wonAtt(int diff)
    {
        for (list<BlackCard *>::iterator it = army->begin(); it != army->end(); ++it)
        {
            if ((*it)->getIsTapped() && (*it)->getPower(true) >= diff)
            {
                it = army->erase(it);
            }
        }
    }

    int getHoldingsNum()
    {
        return h->size();
    }

    void removeHolding(int selected)
    {
        int k = 0;
        for (list<BlackCard *>::iterator it = h->begin(); it != h->end(); ++it)
        {
            if (k == selected)
            {
                h->erase(it);
                break;
            }
            k++;
        }
    }
};

class GameBoard
{
private:
    Player **p;
    int player_num;
    int fixed_player_num;

public:
    GameBoard(int num)
    {
        //cout << "create gameboard\n";
        player_num = num;
        fixed_player_num = player_num;
    }
    ~GameBoard()
    {
        //cout << "delete gameboard\n";
        for (int i = 0; i < fixed_player_num; i++)
            delete p[i];
        delete[] p;
    }
    void initializeGameBoard()
    {
        p = new Player *[player_num];
        for (int i = 0; i < player_num; i++)
            p[i] = new Player(i);
    }
    void printGameStatistics()
    {
        cout << "There are " << player_num << " players in this game." << endl;
    }

    void printPlayers(int myName)
    {
        cout << "Players:" << endl;
        cout << "=============" << endl;
        for (int i = 0; i < player_num; i++)
        {
            if (p[i]->getName() != myName)
                cout << " - " << p[i]->getName() << endl;
        }
    }

    int getPlayerIndex(int name)
    {
        for (int i = 0; i < player_num; i++)
        {
            if (p[i]->getName() == name)
            {
                return i;
            }
        }
        return -1;
    }

    void gameplay()
    {
        int stage, i, j, max;
        int selected, tmp;
        Player *temp;
        for (i = 0; i < player_num; i++)
        {
            max = i;
            for (j = i + 1; j < player_num; j++)
            {
                if ((p[j])->get_honor() > (p[max])->get_honor())
                    max = j;
            }
            temp = p[max];
            p[max] = p[i];
            p[i] = temp;
        }
        while (1)
        {
            for (i = 0; i < player_num; i++)
            {
                //calculate honour ??
                for (stage = 1; stage <= 5; stage++)
                {
                    if (stage == 1)
                        p[i]->startingPhase();
                    if (stage == 2)
                        p[i]->equipPhase();
                    if (stage == 3)
                    {
                        p[i]->battlePhase();
                        if (p[i]->get_army())
                        {
                            cout << "You have no army to prepare for battle..." << endl;
                            getchar();
                            continue;
                        }
                        cout << "Do you want to attack(1) or not(0)?" << endl;
                        cin.clear(); //so that it waits for new cin
                        cin >> tmp;
                        if (tmp == 1)
                        {
                            printPlayers(p[i]->getName());
                            tmp = -1;
                            while (tmp == -1)
                            {
                                cout << "Who do you wish to attack? or -1 to exit" << endl;
                                cin.clear();
                                cin >> tmp;
                                if (tmp == -1)
                                    break;
                                tmp = getPlayerIndex(tmp);
                            }
                            if (tmp == -1)
                                continue;
                            j = tmp;
                        }
                        else
                            continue;
                        p[j]->printHoldings(true);
                        tmp = -1;
                        while (p[j]->getHoldingsNum() != 0)
                        {
                            cout << "Select card (0 - " << p[j]->getHoldingsNum() - 1 << ") or -1 to continue:" << endl;
                            cin.clear(); //so that it waits for new cin
                            cin >> tmp;
                            if (tmp == -1)
                                break;
                            if (tmp < -1 || tmp >= p[j]->getHoldingsNum())
                                cout << "No such card..." << endl;
                            else
                            {
                                selected = tmp;
                                break;
                            }
                        }
                        if (tmp == -1 || p[j]->getHoldingsNum() == 0)
                            continue;
                        //calculate defense and attack for each army
                        if (p[i]->sumAttack() > p[j]->sumDefense())
                        {
                            p[j]->lost();
                            p[i]->wonAtt(p[i]->sumAttack() - p[j]->sumDefense());
                            p[j]->removeHolding(selected);
                            cout << "Holding " << selected << " destroyed" << endl;
                            if (p[j]->getHoldingsNum() == 0)
                            { //you lose
                                cout << "Player " << j << " lost" << endl;
                                //sort so players that lost are last in the array and lower the player num
                                Player *tempPlayer;
                                tempPlayer = p[player_num - 1];
                                p[player_num - 1] = p[j];
                                p[j] = tempPlayer;
                                player_num--;
                            }
                        }
                        else if (p[i]->sumAttack() == p[j]->sumDefense())
                        {
                            p[i]->lost();
                            p[j]->lost();
                        }
                        else if (p[i]->sumAttack() < p[j]->sumDefense())
                        {
                            p[i]->lost();
                        }
                    }
                    if (stage == 4)
                        p[i]->economyPhase();
                    if (stage == 5)
                        p[i]->finalPhase();
                }
                if (checkWinningCondition())
                    return;
            }
        }
    }
    bool checkWinningCondition()
    {
        if (player_num == 1)
        {
            cout << endl
                 << "\\ \\        / (_)  " << endl;
            cout << " \\ \\  /\\  / / _ _ __  _ __   ___ _ __ " << endl;
            cout << "  \\ \\/  \\/ / | | '_ \\| '_ \\ / _ \\ '__|" << endl;
            cout << "   \\  /\\  /  | | | | | | | |  __/ |   " << endl;
            cout << "    \\/  \\/   |_|_| |_|_| |_|\\___|_|  " << endl
                 << endl;
            getchar();
            cout << "Player " << p[0]->getName() << " Won !" << endl;
            return true;
        }
        return false;
    }
};

int get_cost(int);

Card::Card(string n, int x)
{
    name = n;
    cost = get_cost(x);
    isTapped = 0; /////
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
    isReleaved = 0; ////////
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
    setHarvestValue(10);
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

int main(int argc, char *argv[])
{
    srand(unsigned(time(NULL)));
    if (atoi(argv[1]) < 2 || atoi(argv[1]) > 8)
    {
        cout << "Please give a gamer count between 2 and 8!" << endl;
        return -1;
    }
    GameBoard *gameboard = new GameBoard(atoi(argv[1]));
    gameboard->initializeGameBoard();
    gameboard->gameplay();
    delete gameboard;
    return 0;
}