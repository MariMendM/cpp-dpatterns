//============================================================================
// Name        : DP_Prototype.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Prototype Design Pattern in C++, Ansi-style
//============================================================================
//- When new objects (instances) need to be created by cloning (copying) others
//- Allows for adding of any subclass instance of a know superclass at runtime
//- When there are numerous potential classes that you want to only use if needed
//  at runtime
//- Reduces the need for creation of subclasses
//============================================================================

#include <iostream>
using namespace std;

class Animal {
	public:
		virtual Animal *makeCopy() = 0;
		virtual ~Animal() {}
};
class Sheep : public Animal {
	public:
		Sheep () { cout << "\tSheep created" << endl; }
		Animal * makeCopy() { cout << "\tSheep is being created... "; return new Sheep(*this); }
};

class CloneFactory {
	public:
		Animal *getClone (Animal *animalSample) { return animalSample->makeCopy(); }
};

int main() {

	CloneFactory *animalMaker = new CloneFactory();

	cout << "Creating original sheep by new()" << endl;
	Animal *sally = new Sheep();

	cout << "Cloning sheep by getClone()" << endl;
	Animal *sallyClone = animalMaker->getClone(sally);

	cout << endl << sally << endl << sallyClone << endl;

	delete animalMaker;
	delete sally;
	delete sallyClone;

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
