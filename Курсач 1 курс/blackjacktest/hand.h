#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <string>
using namespace std;

class Hand {
  public:
    int getScore() {
      return score;
    }

    void addCard(pair<string, int> card) {
      playedCards.push_back(card);
      score += card.second;
      if (card.first == "A") {
        haveAce ++;
      }
      if (haveAce and score > 21) {
        score -= 10;
        haveAce --;
      }
      if (score >= 21){
          endedTurn = 1;
      }
    }

    bool canSplit() {
      if (playedCards.size() == 2 and playedCards[0].second == playedCards[1].second) {
        return true;
      }
      return false;
    }

    pair<string, int> Split() {
        score -= playedCards.back().second;
        if (haveAce == 1){
            score += 10;
        }
      playedCards.pop_back();
      return playedCards.back();
    }

    void endTurn() {
      endedTurn = true;
    }

    bool isEndedTurn() {
      return endedTurn;
    }

    vector<pair<string, int>> getCards(){
        return playedCards;
    }

    pair<string, int> getFirstCard(){
        return playedCards[0];
    }

  private:
    int haveAce = 0;
    bool endedTurn = false;
    int score = 0;
    vector<pair<string, int>> playedCards;
};

#endif
