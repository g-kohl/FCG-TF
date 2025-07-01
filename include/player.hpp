#pragma once

// C++ headers
#include <iostream>

class Player{
    public:
    int life, money;

    Player();
    void discountLife(int damage);
    bool lost();
    void discountMoney(int price);
    bool canBuy(int price);

    private:

};