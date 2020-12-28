//============================================================================
// Name        : DP_Factory.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Design Pattern Factory in C++, Ansi-style
//============================================================================
//When a method returns one of several possible classes that share a common
//super class. For example, we need to create a new enemy in a game; a random
//number generator picks one of the numbers assigned to one of several enemies
//and the factory object returns the dynamically created enemy associated to
//picked number.
//This illustrates the capacity of factory to choose classes at runtime. Used:
//- when you don't know ahead of time what class object do you need
//- When all of the potential classes are in the same subclass hierarchy
//- To centralize class selection code
//- When toy don't what user to have to know every subclass
//- To encapsulate object creation
//============================================================================


#include <iostream>
#include <limits> //cin.ignore

using namespace std;

//--------------------------------------------------------------------

namespace Attempt1 {
	class EnemyShip {
		private:
			string name;
			double amtDamage;
		public:
			void setName(string s) { name = s; }
			string getName() { return name; }
			void setDamage(double d) { amtDamage = d; }
			double getDmage() { return amtDamage; }

			void folowHeroShip() { cout << "\t" << name << " is following hero!" << endl; }
			void displayEnemyShip() { cout << "\t" << name << " is on the screen!" << endl; }
			void enemyShipShoots() { cout << "\t" << name << " attacks and does " << amtDamage << " damage!" << endl; }
	};
	class UFOEnemyShip : public EnemyShip{
		public:
			UFOEnemyShip () { setName("UFO E.S."); setDamage(20.0); }
	};
	class BigUFOEnemyShip : public EnemyShip{
		public:
			BigUFOEnemyShip () { setName("BigUFO E.S."); setDamage(40.0); }
	};
	class RocketEnemyShip : public EnemyShip{
		public:
			RocketEnemyShip () { setName("Rocket E.S."); setDamage(10.0); }
	};
	//--------------------------------------------------------
	//attention! it is not inside class, just a global function
	void doStuffEnemy(EnemyShip *es) {
		es->displayEnemyShip();
		es->folowHeroShip();
		es->enemyShipShoots();
	}
}

namespace Attempt2 {
	class EnemyShip {
		private:
			string name;
			double amtDamage;
		public:
			void setName(string s) { name = s; }
			string getName() { return name; }
			void setDamage(double d) { amtDamage = d; }
			double getDmage() { return amtDamage; }

			void folowHeroShip() { cout << "\t" << name << " is following hero!" << endl; }
			void displayEnemyShip() { cout << "\t" << name << " is on the screen!" << endl; }
			void enemyShipShoots() { cout << "\t" << name << " attacks and does " << amtDamage << " damage!" << endl; }
	};
	class UFOEnemyShip : public EnemyShip{
		public:
			UFOEnemyShip () { setName("UFO E.S."); setDamage(20.0); }
	};
	class BigUFOEnemyShip : public EnemyShip{
		public:
			BigUFOEnemyShip () { setName("BigUFO E.S."); setDamage(40.0); }
	};
	class RocketEnemyShip : public EnemyShip{
		public:
			RocketEnemyShip () { setName("Rocket E.S."); setDamage(10.0); }
	};

	class EnemyShipFactory{
		public:
			EnemyShip *makeEnemyShip(int shipCode) {
				switch (shipCode) {
					case 1: return new UFOEnemyShip(); break;
					case 2: return new BigUFOEnemyShip(); break;
					case 3: return new RocketEnemyShip(); break;
					default: return nullptr;
				}
			}
	};

	//--------------------------------------------------------
	//attention! it is not inside class, just a global function
	void doStuffEnemy(EnemyShip *es) {
		es->displayEnemyShip();
		es->folowHeroShip();
		es->enemyShipShoots();
	}
}
//--------------------------------------------------------------------



int main() {

	{
		//Static way of doing things... does not fulfill the purpose... =/
		cout << "Regular way of doing things... not nice!" << endl;
		Attempt1::EnemyShip *ufoShip = new Attempt1::UFOEnemyShip();
		Attempt1::doStuffEnemy(ufoShip);
		delete ufoShip;
		cout << endl;
	}

	{
		cout << "Second regular way of doing things... not nice!" << endl;
		int x = 0;
		do {
			cout << "\tWhat number of ship? (1)Ufo / (2)BigUfo / (3)Rocket >>>  ";
			cin >> x;
			cin.clear(); cin.ignore (numeric_limits<streamsize>::max(), '\n'); //Fica um ENTER no buffer
		} while (x < 1 || x > 3 || cin.fail());

		//It is kind of dynamic, but it does not prevent code form changing when new enemy ships
		//are added/removed. Besides, it can bring lots of if/else to code itself... not nice!
		Attempt1::EnemyShip *ship;
		switch (x) {
			case 1: ship = new Attempt1::UFOEnemyShip(); break;
			case 2: ship = new Attempt1::BigUFOEnemyShip(); break;
			case 3: ship = new Attempt1::RocketEnemyShip(); break;
		}

		Attempt1::doStuffEnemy(ship);
		delete ship;
		cout << endl;
	}

	{
		cout << "Using Factory, finally!" << endl;
		int x = 0;
		do {
			cout << "\tWhat number of ship? (1)Ufo / (2)BigUfo / (3)Rocket >>>  ";
			cin >> x;
			cin.clear(); cin.ignore (numeric_limits<streamsize>::max(), '\n'); //Fica um ENTER no buffer
		} while (x < 1 || x > 3 || cin.fail());

		//Clear; simple; factory!
		Attempt2::EnemyShipFactory *shipFactory = new Attempt2::EnemyShipFactory();
		Attempt2::EnemyShip *ship;
		ship = shipFactory->makeEnemyShip(x);
		//good to implement some exception handlers here...

		Attempt2::doStuffEnemy(ship);

		delete shipFactory;
		delete ship;
	}

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
