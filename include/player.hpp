#pragma once

// C++ headers
#include <iostream>

class Player{
    public:
        Player(int life=1, int money=200, bool strategyMode=false);

        // life
        void discountLife(int damage);
        bool lost();

        // money
        bool canBuy(int price);
        void discountMoney(int price);
        void giveMoney(int cash);

        // strategy mode
        bool inStrategyMode();
        void setStrategyMode(bool status);

    private:
        int life, money;
        bool strategyMode;
};