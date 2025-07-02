#include "player.hpp"

Player player = Player();
bool inStrategyMode;

Player::Player(){
    life = 0;
    money = 100;
}

void Player::discountLife(int damage){
    life -= damage;
}

bool Player::lost(){
    if(life < 0)
        return true;

    return false;
}

void Player::discountMoney(int price){    
    money -= price;
}

bool Player::canBuy(int price){
    if(money - price >= 0)
        return true;

    return false;
}