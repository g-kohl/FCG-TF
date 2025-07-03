#pragma once

// C++ headers
#include <iostream>

class Player{
    public:
        Player(int life=1, int money=100, bool strategyMode=false);

        void discountLife(int damage);
        bool lost();

        void discountMoney(int price);
        void giveMoney(int cash);
        bool canBuy(int price);

        bool inStrategyMode();
        void setStrategyMode(bool status);

    private:
        int life, money;
        bool strategyMode;
};