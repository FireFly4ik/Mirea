#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "hand.h"
#include <vector>
#include "bits-stdc++.h"
#include <QDebug>
using namespace std;

vector<Hand*> allPlayerHands;
vector<pair<string, int>> pack {{"K", 10}, {"Q", 10}, {"J", 10}, {"10", 10}, {"9", 9}, {"8", 8}, {"7", 7}, {"6", 6}, {"5", 5}, {"4", 4}, {"3", 3}, {"2", 2}, {"A", 11}}; // все карты в колоде и их стоимость в игре
vector<pair<string, int>> activePack; // активная игровая колода
int activeHandIndex = 1;
Hand* dealerHand = new Hand();
Hand* playerHand = new Hand();
bool endedPack = 1;
int deletableNumberOfCards;

// получить рандомную карту если колода закончилась
pair<string, int> getRandomCard() {
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<> distrib(0, 12);
    return pack[distrib(g)];
}

// взять карту, действие кнопки Add
pair<string, int> getCard(int ind) {
    Hand* hand = allPlayerHands[ind];
    pair<string, int> addedCard;
    if (activePack.size() == 0) {
        addedCard = getRandomCard();
        hand->addCard(addedCard);
    } else {
        if (deletableNumberOfCards >= activePack.size()){
            endedPack = 1;
        }
        addedCard = activePack[0];
        hand->addCard(activePack[0]);
        activePack.erase(activePack.begin());
    }
    return addedCard;
}

bool checkSplit(){
    return activeHandIndex >= allPlayerHands.size() ? false : allPlayerHands[activeHandIndex]->canSplit();
}

bool checkEnd(){
    return allPlayerHands[activeHandIndex]->isEndedTurn();
}

int checkScore(int x){
    return allPlayerHands[x]->getScore();
}

// действие кнопки Split
void splitCards() {
    Hand* newHand = new Hand();
    allPlayerHands.push_back(newHand);
    pair<string, int> splittedCard = allPlayerHands[activeHandIndex]->Split();
    newHand->addCard(splittedCard);
}

// остановка хода игрока, действие кнопки Stay
void stayCard() {
    allPlayerHands[activeHandIndex]->endTurn();
    activeHandIndex ++;
}

pair<string, int> getFirstDealerCard(){
    return dealerHand->getFirstCard();
}

pair<string, int> dealerStart(){
    pair<string, int> addedCard;
    if (activePack.size() == 0) {
        addedCard = getRandomCard();
        dealerHand->addCard(addedCard);
    } else {
        if (deletableNumberOfCards >= activePack.size()){
            endedPack = 1;
        }
        addedCard = activePack[0];
        dealerHand->addCard(activePack[0]);
        activePack.erase(activePack.begin());
    }
    return dealerHand->getFirstCard();
}

void playGame(){
    for (int i = 0; i < allPlayerHands.size(); i++){
        delete allPlayerHands[i];
    }
    allPlayerHands.clear();
    playerHand = new Hand;
    dealerHand = new Hand;
    allPlayerHands.push_back(dealerHand);
    allPlayerHands.push_back(playerHand);
    activeHandIndex = 1;
}

void shuffle(){
    activePack.clear();
    int numberOfPacks = 32; // количество колод в игре
    for (int i = 0; i < numberOfPacks; i++) {
        activePack.insert(activePack.end(), pack.begin(), pack.end());
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(activePack.begin(), activePack.end(), g);
    uniform_int_distribution<> distrib(28, 37);
    deletableNumberOfCards = distrib(g) * activePack.size() / 100;
    endedPack = 0;
}

void createGame(){
    shuffle();
    playGame();
}

vector<pair<string, int>> dealerTurn(){
    while(dealerHand->getScore() < 17){
        pair<string, int> addedCard;
        if (activePack.size() == 0) {
            addedCard = getRandomCard();
            endedPack = true;
            dealerHand->addCard(addedCard);
        } else {;
            if (deletableNumberOfCards >= activePack.size()){
                endedPack = 1;
            }
            addedCard = activePack[0];
            dealerHand->addCard(activePack[0]);
            activePack.erase(activePack.begin());
        }
    }
    return dealerHand->getCards();
}

#endif
