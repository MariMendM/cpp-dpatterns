//============================================================================
// Name        : DP_AsbtractFactory.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Design Pattern Abstract Factory in C++, Ansi-style
//============================================================================
//It is like Factory Pattern, but everything is encapsulated:
//- the method that orders the object
//- the factory that builds the object
//- the final objects
//Also, the final objects contain objects that use the Strategy Pattern.
//It allows you to create families of related objects without specifying a
//concrete class. Use when you have many objects that can be added/changed
//dynamically during runtime.
//Bad part of it: things can get complicated...
//============================================================================

#include <iostream>
using namespace std;

class EnemyShip;
class ESWeapon;
class ESEngine;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// CLASS INTERFACES
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

//------------------------------------------------------------------------------------
//INTERFACE ENEMYSHIPBUILDING and derived UFOENEMYSHIPBUILDING/ROCKETENEMYSHIPBUILDING
//------------------------------------------------------------------------------------
//who makes the order? the "abstract order form" aka EnemyShipBuilding!
//------------------------------------------------------------------------------------
class EnemyShipBuilding {
	protected:
		virtual EnemyShip *makeEnemyShip(string typeOfShip) = 0;
	public:
		virtual ~EnemyShipBuilding() {}
		EnemyShip *orderTheShip(string typeOfShip); //Executes 'makeEnemyShip'
};

//When it comes to EnemyShipBuilding for UFOs, the below class deals with
//the order, determining inside 'makeEnemyShip' what kind of factories exist for UFOs
class UFOEnemyShipBuilding : public EnemyShipBuilding {
	protected:
		EnemyShip *makeEnemyShip(string typeOfShip);
};

//When it comes to EnemyShipBuilding for Rockets, RockectEnemyBuilding does the job
class RocketEnemyShipBuilding : public EnemyShipBuilding {
	protected:
		EnemyShip *makeEnemyShip(string typeOfShip);
};
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//INTERFACES ENEMYSHIPFACTORY and derived UFOENEMYSHIPFACTORY/ROCKETENEMYSHIPFACTORY
//------------------------------------------------------------------------------------
//These are the factories themselves, the ones that will pop out different types of
//abstract enemy ship classes determining what parts each ship shall include (parts
//defined by composition - STRATEGY PATTERN)
//------------------------------------------------------------------------------------
class EnemyShipFactory{
	public:
		virtual ~EnemyShipFactory() {}
		virtual ESWeapon *addESGun() = 0;		//every ship has a gun
		virtual ESEngine *addESEngine() = 0;	//every ship has an engine
};
class UFOEnemyShipFactory : public EnemyShipFactory {
	public:
		ESWeapon *addESGun();
		ESEngine *addESEngine();
};
class UFOBossEnemyShipFactory : public EnemyShipFactory {
	public:
		ESWeapon *addESGun();
		ESEngine *addESEngine();
};
class RocketEnemyShipFactory : public EnemyShipFactory {
	public:
		ESWeapon *addESGun();
		ESEngine *addESEngine();
};
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//INTERFACE ENEMYSHIP and derived UFOENEMYSHIP/UFOBOSSENEMYSHIP/ROCKETENEMYSHIP
//------------------------------------------------------------------------------------
//The abstract EnemyShip will assure that for every type of ship, the "makeShip" will
//be available...
//------------------------------------------------------------------------------------
class EnemyShip {
	private:
		string name;
		ESWeapon *weapon;
		ESEngine *engine;
	public:
		virtual ~EnemyShip() {}
		virtual void makeShip() = 0;

		void setName(string s);
		void setWeapon(ESWeapon *esw);
		void setEngine(ESEngine *ese);

		string getName();
		//ESWeapon *getWeapon(); //not implemented
		//ESEngine *getEngine(); //not implemented

		void print();

		void folowHeroShip();
		void displayEnemyShip();
		void enemyShipShoots();
};

//Then the classes for different UFO and Rocket ships implement 'makeShip' to use
//factories derived from EnemyShipFactory to add parts pertinent to each type
class UFOEnemyShip : public EnemyShip{
	private:
		EnemyShipFactory *shipFactory;
	public:
		UFOEnemyShip(EnemyShipFactory *shipFact);
		void makeShip();
};
class UFOBossEnemyShip : public EnemyShip{
	private:
		EnemyShipFactory *shipFactory;
	public:
		UFOBossEnemyShip(EnemyShipFactory *shipFact);
		void makeShip();
};
class RocketEnemyShip : public EnemyShip{
	private:
		EnemyShipFactory *shipFactory;
	public:
		RocketEnemyShip(EnemyShipFactory *shipFact);
		void makeShip();
};
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//INTERFACE ESWEAPON and derived ESUFOGun/ESROCKETGUN
//INTERFACE ESENGINE and derived ESUFOENGINE/ESROCKETENGINE
//------------------------------------------------------------------------------------
//Then the classes to attach parts to the ships...
//------------------------------------------------------------------------------------
class ESWeapon {
	public:
		virtual ~ESWeapon() {}
		virtual string print() = 0;
};
class ESUFOGun : public ESWeapon {
	public:
		string print();
};
class ESUFOBossGun : public ESWeapon {
	public:
		string print();
};
class ESRocketGun : public ESWeapon {
	public:
		string print();
};
//------------------------------------------------------------------------------------
class ESEngine {
	public:
		virtual ~ESEngine() {}
		virtual string print() = 0;
};
class ESUFOEngine : public ESEngine {
	public:
		string print();
};
class ESRocketEngine : public ESEngine {
	public:
		string print();
};
//------------------------------------------------------------------------------------


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// CLASS IMPLEMENTATIONS
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

//------------------------------------------------------------------------------------
//IMPLEMENTATION EnemyShipBuilding
//------------------------------------------------------------------------------------
EnemyShip *EnemyShipBuilding::orderTheShip(string typeOfShip) {
		EnemyShip *eship = makeEnemyShip(typeOfShip);
		eship->makeShip();
		eship->displayEnemyShip();
		eship->folowHeroShip();
		return eship;
}

//------------------------------------------------------------------------------------
//IMPLEMENTATION UFOEnemyShipBuilding
//------------------------------------------------------------------------------------
EnemyShip *UFOEnemyShipBuilding::makeEnemyShip(string typeOfShip) {
	EnemyShip *eship = nullptr;
	if (typeOfShip == "UFO") {
		EnemyShipFactory *shipPartsFact = new UFOEnemyShipFactory();
		eship = new UFOEnemyShip(shipPartsFact);
		eship->setName("UFO Grunt Ship");
		return eship;
	}
	if (typeOfShip == "UFO Boss") {
		EnemyShipFactory *shipPartsFact = new UFOBossEnemyShipFactory();
		eship = new UFOBossEnemyShip(shipPartsFact);
		eship->setName("UFO Boss Ship");
		return eship;
	}
	return nullptr; //if none of the conditions
}

//------------------------------------------------------------------------------------
//IMPLEMENTATION RocketEnemyShipBuilding
//------------------------------------------------------------------------------------
EnemyShip *RocketEnemyShipBuilding::makeEnemyShip(string typeOfShip) {
	EnemyShip *eship = nullptr;
	if (typeOfShip == "Rocket") {
		EnemyShipFactory *shipPartsFact = new RocketEnemyShipFactory();
		eship = new RocketEnemyShip(shipPartsFact);
		eship->setName("Rocket Grunt Ship");
		return eship;
	}
	return nullptr; //if none of the conditions
}

//------------------------------------------------------------------------------------
//IMPLEMENTATION UFOEnemyShipFactory
//------------------------------------------------------------------------------------
ESWeapon *UFOEnemyShipFactory::addESGun()	 { return new ESUFOGun(); }
ESEngine *UFOEnemyShipFactory::addESEngine() { return new ESUFOEngine(); };

//------------------------------------------------------------------------------------
//IMPLEMENTATION UFOBossEnemyShipFactory
//------------------------------------------------------------------------------------
ESWeapon *UFOBossEnemyShipFactory::addESGun()	 { return new ESUFOBossGun(); }
ESEngine *UFOBossEnemyShipFactory::addESEngine() { return new ESUFOEngine(); }

//------------------------------------------------------------------------------------
//IMPLEMENTATION UFOEnemyShipFactory
//------------------------------------------------------------------------------------
ESWeapon *RocketEnemyShipFactory::addESGun()	{ return new ESRocketGun(); }
ESEngine *RocketEnemyShipFactory::addESEngine() { return new ESRocketEngine(); };

//------------------------------------------------------------------------------------
//IMPLEMENTATION ENEMYSHIP
//------------------------------------------------------------------------------------
void EnemyShip::print()            { cout << "\t" << name << " has speed of " << engine->print() << " and attack of " << weapon->print() << endl; }
void EnemyShip::folowHeroShip()    { cout << "\t" << name << " is following hero!" << endl; }
void EnemyShip::displayEnemyShip() { cout << "\t" << name << " is on the screen!" << endl; }
void EnemyShip::enemyShipShoots()  { cout << "\t" << name << " causes " << weapon->print() << "!"<< endl; }
void EnemyShip::setName(string s)  { name = s; }
void EnemyShip::setWeapon(ESWeapon *esw) { weapon = esw; }
void EnemyShip::setEngine(ESEngine *ese) { engine = ese; }
string EnemyShip::getName()        { return name; }

//--------------------------------------------------------
//IMPLEMENTATION UFOENEMYSHIP
//--------------------------------------------------------
UFOEnemyShip::UFOEnemyShip(EnemyShipFactory *shipFact)
{ this->shipFactory = shipFact; }

void UFOEnemyShip::makeShip() {
	cout << "\tMaking enemy ship " << getName() << endl;
	setWeapon (shipFactory->addESGun());
	setEngine (shipFactory->addESEngine());
}

//--------------------------------------------------------
//IMPLEMENTATION UFOBOSSENEMYSHIP
//--------------------------------------------------------
UFOBossEnemyShip::UFOBossEnemyShip(EnemyShipFactory *shipFact)
{ this->shipFactory = shipFact; }

void UFOBossEnemyShip::makeShip() {
	cout << "\tMaking enemy ship " << getName() << endl;
	setWeapon (shipFactory->addESGun());
	setEngine (shipFactory->addESEngine());
}

//--------------------------------------------------------
//IMPLEMENTATION RCOKETENEMYSHIP
//--------------------------------------------------------
RocketEnemyShip::RocketEnemyShip(EnemyShipFactory *shipFact)
{ this->shipFactory = shipFact; }

void RocketEnemyShip::makeShip() {
	cout << "\tMaking enemy ship " << getName() << endl;
	setWeapon (shipFactory->addESGun());
	setEngine (shipFactory->addESEngine());
}

//--------------------------------------------------------
//IMPLEMENTATION ESUFOGun
//--------------------------------------------------------
string ESUFOGun::print() { return "20 damage";}

//--------------------------------------------------------
//IMPLEMENTATION ESUFOBossGun
//--------------------------------------------------------
string ESUFOBossGun::print() { return "40 damage";}

//--------------------------------------------------------
//IMPLEMENTATION ESRocketGun
//--------------------------------------------------------
string ESRocketGun::print() { return "10 damage";}

//--------------------------------------------------------
//IMPLEMENTATION ESUFOENGINE
//--------------------------------------------------------
string ESUFOEngine::print() { return "1000 mph"; }

//--------------------------------------------------------
//IMPLEMENTATION ESRocketENGINE
//--------------------------------------------------------
string ESRocketEngine::print() { return "2000 mph"; }





//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
// PROGRAM
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

void doStuffEnemy(EnemyShip *es) {
	es->displayEnemyShip();
	es->folowHeroShip();
	es->enemyShipShoots();
}

int main() {

	//Explanation of responsibilities of each class inside Abstract Factory:
	//read class interfaces in order top-down in the file


	//The alien comes and order: "I want you to make UFO ships"

	//The sales man then makes the order for UFO ships...
	EnemyShipBuilding *MakeUFOs = new UFOEnemyShipBuilding();
	cout << "Creating theGruntUFO..." << endl;
	EnemyShip *theGruntUFO = MakeUFOs->orderTheShip("UFO");
	cout << "Creating theBossUFO..." << endl;
	EnemyShip *theBossUFO = MakeUFOs->orderTheShip("UFO Boss");

	//But the alien also ordered: "I want you to make Rocket ships"

	//The sales man then makes the order for Rocket ships...
	EnemyShipBuilding *MakeRockets = new RocketEnemyShipBuilding();
	cout << "Creating theGruntRocket..." << endl;
	EnemyShip *theGruntRocket = MakeRockets->orderTheShip("Rocket");

	cout << "Printing theGruntUFO..." << endl;
	theGruntUFO->print();
	cout << "Printing theBossUFO..." << endl;
	theBossUFO->print();
	cout << "Printing theGruntRocket..." << endl;
	theGruntRocket->print();

	cout << "theGruntUFO doing stuff.." << endl;
	doStuffEnemy(theGruntUFO);
	cout << "theBossUFO doing stuff.." << endl;
	doStuffEnemy(theBossUFO);
	cout << "theGruntRocekt doing stuff.." << endl;
	doStuffEnemy(theGruntRocket);

	delete MakeUFOs;
	delete theGruntUFO;
	delete theBossUFO;
	delete MakeRockets;
	delete theGruntRocket;

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
