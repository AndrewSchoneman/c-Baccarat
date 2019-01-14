/*
	@Author Andy Schoneman
	@License freeware you get what you pay for
*/

#ifndef PCH_H
#define PCH_H
#include <vector> 
#include <string>

using namespace std;

class Card 
{
	private:
		string suit;
		int value;

	public:
		Card();
		Card(string s, int num);
		int getValue();
		int cardNum();
		string getSuit();
};

class Deck
{
	private:
		vector<Card>cards;

	public:
		void shuffleDeck();
		Deck();
		Card dealCard();
		void resetDeck();
};

class Player
{

	private:
		vector<Card> hand;
		int handValue;
		string name;
		bool threeCards = false;
		int thirdVal;
		int bank = 200;

	public:
		Player();
		void addToHand(Card c);
		void updateValue(int val);
		void setName(string n);
		void showHand();
		void setBank(int bank);
		void resetHand();
		string getName();
		bool hasThreeCards();
		int thirdCardVal();
		int getValue();
		int getBank();
		
};

class Game
{
	private:
		Player dealer;
		Player user;
		Deck deck;
		int betAmount;
	public:
		Game();
		void deal();
		void checkInitial();
		void tableau();
		void checkWin();
		void playAgain();
		void placeBet();
		void playerWin();
		void tieGame();
		void gameOver();
		void resetHands();
};

#endif //PCH_H