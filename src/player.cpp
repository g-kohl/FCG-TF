#include "player.hpp"

Player player = Player();

// constructor
Player::Player(int life, int money, bool strategyMode)
    : life(life), money(money), strategyMode(strategyMode) {}

// life

void Player::discountLife(int damage){
    life -= damage;
}

bool Player::lost(){
    return life <= 0;
}

// money

bool Player::canBuy(int price){
    return money >= price;
}

void Player::discountMoney(int price){    
    money -= price;
}

void Player::giveMoney(int cash){
    money += cash;
}

// strategy mode

bool Player::inStrategyMode(){
    return strategyMode;
}

void Player::setStrategyMode(bool status){
    strategyMode = status;
}