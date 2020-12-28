//============================================================================
// Name        : DP_Singleton.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Singleton Design Pattern in C++, Ansi-style
//============================================================================
//Use when you want to eliminate the option of instantiating more than object
//For example, if you implement Scrabble Game, you need a single object of a
//class holding all the potential letters and spit out new ones upon request
//============================================================================
//IMPORTANT: if the Singleton pattern is used in a multithreading code, it shall
//have some kind of protection implemented to avoid each thread to allocate its
//own singleton
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <thread>

using namespace std;

namespace PureSingleton {

	//This a singleton class, pure, with no purpose
	class Singleton {
		private:
			static Singleton *uniqueInstance;
			Singleton() {}	//if public, you do not prevent multiple objects!
		public:
			static Singleton *getInstance() {
				if (uniqueInstance == nullptr)
					//Lazy instantiation: if instance is not needed, it will never be created
					uniqueInstance = new Singleton();
				return uniqueInstance;
			}
	};
}


namespace Scrabble {

	class Singleton {
		private:
			static Singleton *uniqueInstance;
			vector<char> scrabbleLetters;
			list<char> letterList;
		private:
			Singleton();
		public:
			~Singleton();
			static Singleton *getInstance();
			list<char> getLetterList();
			list<char> getTiles(int qtd);
	};
	//-------------------------------------------------------------------------
	Singleton::Singleton() {
		scrabbleLetters = \
				{'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', \
				 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', \
				 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i', \
				 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', \
				 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', 'u', \
				 'b', 'b', 'b', 'c', 'c', 'c', 'd', 'd', 'd', 'f', 'f', \
				 'f', 'g', 'g', 'g', 'h', 'h', 'h', 'j', 'j', 'j', 'l', \
				 'l', 'l', 'm', 'm', 'm', 'n', 'n', 'n', 'p', 'p', 'p', \
				 'q', 'q', 'q', 'r', 'r', 'r', 's', 's', 's', 't', 't', \
				 't', 'v', 'v', 'v', 'x', 'x', 'x', 'z', 'z', 'z', 'z'};
		srand(time(0)); //not the best seeding, but...
		random_shuffle(scrabbleLetters.begin(), scrabbleLetters.end());

		letterList.assign(scrabbleLetters.begin(), scrabbleLetters.end());
	}
	//-------------------------------------------------------------------------
	Singleton *Singleton::getInstance() {
		//Lazy instantiation: if instance is not needed, it will never be created
		if (uniqueInstance == nullptr)
			uniqueInstance = new Singleton();
		return uniqueInstance;
	}
	//-------------------------------------------------------------------------
	list<char> Singleton::getLetterList() {
		return uniqueInstance->letterList;
	}
	//-------------------------------------------------------------------------
	list<char> Singleton::getTiles(int qtd) {
		list<char> tilesToSend;
		for (int i=0; i<qtd; ++i) {
			tilesToSend.push_back(uniqueInstance->letterList.front());
			uniqueInstance->letterList.pop_front();
		}
		return tilesToSend;
	}

} //end namespace



using namespace Scrabble;

Singleton *Singleton::uniqueInstance = nullptr;

int main() {

	//NO THREADING...
	cout << "SET OF LETTERS FROM SCRABBLE:" << endl;
	list<char> letterList = Singleton::getInstance()->getLetterList();
	for (auto elem : letterList) {cout << elem << " ";} cout << endl;

	cout << "SET OF LETTERS OF PLAYER 1:" << endl;
	list<char> player1Tiles = Singleton::getInstance()->getTiles(7);
	for (auto elem : player1Tiles) {cout << elem << " ";} cout << endl;

	cout << "SET OF LETTERS OF PLAYER 1:" << endl;
	list<char> player2Tiles = Singleton::getInstance()->getTiles(7);
	for (auto elem : player2Tiles) {cout << elem << " ";} cout << endl;

	//THREADING...

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}


