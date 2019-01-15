// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <random>
using namespace::std;

// Card
/***************************************************/

int Card::getValue()
{
	if (value >= 2 && value <= 9) 
	{
		return value;
	}
	else if (value > 9 && value < 14) 
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

Card::Card(string s, int num) 
{
	Card::suit = s;
	Card::value = num;
}

Card::Card()
{
	Card::suit = "null";
	Card::value = -1;
}

int Card::cardNum()
{
	return value;
}

string Card::getSuit()
{
	return suit;
}

// Deck
/***************************************************/

Deck::Deck() 
{
	resetDeck();
}

void Deck::resetDeck()
{
	cards.clear();
	for (int i = 2; i <= 14; i++)
	{
		cards.push_back(Card("Heart", i));
		cards.push_back(Card("Spade", i));
		cards.push_back(Card("Club", i));
		cards.push_back(Card("Diamond", i));
	}
	shuffleDeck();
}


void Deck::shuffleDeck() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	shuffle(cards.begin(), cards.end(), e);
}
Card Deck::dealCard()
{
	Card $card = cards.back();
	cards.pop_back();
	return $card;
}


// Player
/***************************************************/
Player::Player()
{
	name = "Dealer";
}

void Player::setName(string n)
{
	name = n;
}

string Player::getName()
{
	return name;
}
void Player::addToHand(Card c)
{
	hand.push_back(c);
	updateValue(c.getValue());
	if (hand.size() == 3)
	{
		thirdVal = c.getValue();
		threeCards = true;

	}
}
void Player::updateValue(int val)
{
	handValue += val;
	if (handValue >= 10 && handValue < 20) handValue -= 10;
	else if (handValue >= 20) handValue -= 20;
	else if (handValue >= 30) handValue -= 30;
}

int Player::getValue() 
{
	return handValue;
}
int Player::thirdCardVal()
{
	return thirdVal;
}

bool Player::hasThreeCards()
{
	return threeCards;
}
int Player::getBank()
{
	return bank;
}
void Player::setBank(int bank)
{
	this->bank = bank;
}

void Player::showHand()
{
	string info = +"\n" + name + " Hand:\n"; 
	for (Card &card : hand)
	{
		if (card.cardNum() == 14) info += "Ace " + card.getSuit() + ", ";
		else if (card.cardNum() == 13) info += "King " + card.getSuit() + ", ";
		else if (card.cardNum() == 12) info += "Queen " + card.getSuit() + ", ";
		else if (card.cardNum() == 11) info += "Jack " + card.getSuit() + ", ";
		else 
		{
			info += to_string(card.cardNum()) + " ";
			info += card.getSuit() + ", ";
		}
	}
	cout << info << endl;
	cout << "Hand Value: " << to_string(handValue) << "\n\n";
}
void Player::resetHand()
{
	hand.clear();
	handValue = 0;
	threeCards = false;
	thirdVal = NULL;
}
// Game
/***************************************************/
Game::Game()
{
	string name;
	cout << "Plese enter your name: \n";
	cin >> name;
	user.setName(name);
	deal();
}
void Game::deal()
{
	placeBet();
	for (int i = 0; i < 2; ++i)
	{
		deck.dealCard();
		user.addToHand(deck.dealCard());
		deck.dealCard();
		dealer.addToHand(deck.dealCard());		
	}

	user.showHand();
	dealer.showHand();
	checkInitial();
}
void Game::checkInitial()
{
	if ((user.getValue() == 8 || user.getValue() == 9) &&
		(dealer.getValue() == 8 || dealer.getValue()) == 9)
	{
		tieGameOutcome();
	}
	else if (user.getValue() == 8 || user.getValue() == 9)
	{
		playerWinOutcome();
	}
	else if (dealer.getValue() == 8 || dealer.getValue() == 9)
	{
		dealerwinOutcome();
	}
	else 
	{
		cout << "Consulting the tableau............." << endl << endl;
		tableau();
	}
}

void Game::tableau()
{
	if (user.getValue() >= 0 && user.getValue() <= 5)
	{
		deck.dealCard();
		user.addToHand(deck.dealCard());
		cout << "Dealing to " << user.getName()  << "..........\n\n";
	}
	if (user.hasThreeCards()) {
		if (dealer.getValue() <= 2)
		{
			dealToDealer();
		}
		else if (user.thirdCardVal() != 8 && dealer.getValue() == 3)
		{
			dealToDealer();
		}
		else if ( user.thirdCardVal() >= 2 && user.thirdCardVal() <= 7 
					&& dealer.getValue() == 4)
		{
			dealToDealer();
		}
		else if (user.thirdCardVal() >= 4 && user.thirdCardVal() <= 7 
					&& dealer.getValue() == 5)
		{
			dealToDealer();
		}
		else if (user.thirdCardVal() != 6 && user.thirdCardVal() != 7
			&& dealer.getValue() == 6)
		{
			dealToDealer();
		}
	}
	user.showHand();
	dealer.showHand();
	checkWin();
}
void Game::dealToDealer()
{
	deck.dealCard();
	dealer.addToHand(deck.dealCard());
	cout << "Dealing to Dealer..........\n\n";
}

void Game::checkWin()
{
	if (user.getValue() ==  dealer.getValue())
	{
		tieGameOutcome();
	}
	else if (user.getValue() > dealer.getValue())
	{
		playerWinOutcome();
		
	}
	else
	{
		dealerwinOutcome();
	}
}
void Game::playAgain() 
{
	string play;
	gameOver();
	cout << "\nYou have " << user.getBank() << " left in your bank";
	cout << "\nWould you like to play again?\n";
	while (true)
	{
		cin >> play;
		cout << endl;
		std::transform(play.begin(), play.end(), play.begin(), ::tolower);
		if (play == "yes")
		{
			deck.resetDeck();
			resetHands();
			deal();
		}
		else if (play == "no")
		{
			cout << "Goodbye\n";
			exit(0);
		}
		else
		{
			cout << "Sorry command " << play << " Not recognized\n";
			cout << "Type yes to play again or no to quit\n\n";
		}
	}
}
void Game::placeBet()
{
	int bet;
	cout << "\n" << user.getName() <<  " you have " << user.getBank() << " left in your bank";
	cout << " Enter a bet amount:\n";

	while (true)
	{
		
		cin >> bet;
		cout << endl;
		if (bet > 0 && user.getBank() - bet >= 0)
		{
			betAmount = bet;
			user.setBank(user.getBank() - bet);
			break;
		}
		else
		{
			if (user.getBank() - bet < 0) 
			{
				cout << "Sorry the bet " << bet << " is more money than you have\n";
				cout << "You have " << user.getBank() << " dollars\n";
				cout << "Please enter a bet\n";
			}
			else
			{
				cout << "Not a valid bet. Please enter a valid bet\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}
}
void Game::tieGameOutcome()
{
	cout << "The game has tied" << endl;
	cout << "Dealer: " << user.getValue() << " " << "User: " << user.getValue() << endl;
	tieGame();
	playAgain();
}
void Game::dealerwinOutcome()
{
	cout << "The Dealer has won" << endl;
	cout << "Dealer: " << dealer.getValue() << " " << "User: " << user.getValue() << endl;
	playAgain();
}
void Game::playerWinOutcome()
{
	cout << "The Player has won" << endl;
	cout << "Dealer: " << dealer.getValue() << " " << "User: " << user.getValue() << endl;
	playerWin();
	playAgain();
}

void Game::resetHands()
{
	user.resetHand();
	dealer.resetHand();
}
void Game::playerWin()
{
	user.setBank(user.getBank() + (betAmount * 2));
}

void Game::tieGame()
{
	user.setBank(user.getBank() + betAmount);
}

void Game::gameOver()
{
	if (user.getBank() <= 0) 
	{
		cout << "\nGame over you went bankrupt\n";
		exit(0);
	}
}

int main()
{
	Game game;
	
}