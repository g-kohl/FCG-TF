#include "player.hpp"

Player player = Player();

Player::Player(int life, int money, bool strategyMode)
    : life(life), money(money), strategyMode(strategyMode) {}

void Player::discountLife(int damage){
    life -= damage;
}

bool Player::lost(){
    return life <= 0;
}

void Player::discountMoney(int price){    
    money -= price;
}

void Player::giveMoney(int cash){
    money += cash;
}

bool Player::canBuy(int price){
    return money >= price;
}

bool Player::inStrategyMode(){
    return strategyMode;
}

void Player::setStrategyMode(bool status){
    strategyMode = status;
}