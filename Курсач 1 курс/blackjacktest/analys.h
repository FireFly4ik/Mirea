#ifndef ANALYS_H
#define ANALYS_H

#include <QDebug>
#include "playGame.h"

int playedGames = 0;
int takedCards = 0;
int playedCards = 0;
int winnedHands = 0;
int playedHands = 0;

void addGame (int currentPlayedCards, int currentTakedCards, int currentPlayedHands){
    playedGames ++;
    playedCards += currentPlayedCards;
    takedCards += currentTakedCards;
    playedHands += currentPlayedHands;
}

float checkChance(int x) {
    int currentScore = checkScore(x);
    int lengthOfPack = activePack.size();

    if (lengthOfPack == 0 || currentScore >= 21) return 0.0f;

    int safeCards = 0;

    for (const auto& card : activePack) {
        int cardValue = card.second;
        if (cardValue == 11) {
            cardValue = 1;
        }
        if (currentScore + cardValue <= 21)
            safeCards++;
    }

    float chance = float(safeCards) / float(lengthOfPack);
    return chance;
}

#endif // ANALYS_H
