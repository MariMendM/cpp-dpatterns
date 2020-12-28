//============================================================================
// Name        : DP_Template.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Template Design Pattern in C++, Ansi-style
//============================================================================
//- Used to create a group of subclasses that have to execute a similar group
//  of methods
//- You create an abstract class that contains a method called TemplateMethod
//- The TemplateMethod contains a series of method calls that every subclass
//  object will call
//- The subclass objects can override some of the method calls
//============================================================================

#include <iostream>
#include <list>
using namespace std;

//First possibility is to create a class for each Hoagie and implement
//what is necessary to make it. The problem is that many of the methods
//could be used for other Hoagies, which implies in duplicate of code...

namespace Attempt1 {
	class ItalianHoagie {
		public:
			void makeSandwich() {
				cutBun();
				addMeat();
				addCheese();
				addVegetables();
				addCondiments();
				wrapTheHoagie();
			}
			void cutBun() { cout << "\tHoagie is cut!" << endl; }
			void addMeat() { cout << "\tAdded meat!" << endl; }
			void addCheese() { cout << "\tAdded cheese!" << endl; }
			void addVegetables() { cout << "\tAdded vegetables!" << endl; }
			void addCondiments() { cout << "\tAdded condiments!" << endl; }
			void wrapTheHoagie() { cout << "\tHoagie wraped!" << endl; }
	};
}

//Let's then do the right way, using templates...

class Hoagie {
	public:
		virtual ~Hoagie() {}
		virtual void makeSandwich () final {   //TemplateMethod; final: no one can override it!
			cutBun();
			if (customerWantsMeat()) addMeat();
			if (customerWantsCheese()) addCheese();
			if (customerWantsVegetables()) addVegetables();
			if (customerWantsCondiments()) addCondiments();
			wrapTheHoagie();
		}
		void cutBun() { cout << "\tHoagie is cut!" << endl; }
		void wrapTheHoagie() { cout << "\tHoagie wrapped!" << endl; }

		//abstract methods: mandatory override in subclasses (can be implemented here
		//in case they are exactly the same for all subclasses; in this example, we could;
		//but let's override just for fun!)
		virtual void addMeat() = 0;
		virtual void addCheese() = 0;
		virtual void addVegetables() = 0;
		virtual void addCondiments() = 0;

		//hooks: optional to be overridden in subclasses
		bool customerWantsMeat() { return true; }
		bool customerWantsCheese() { return true; }
		bool customerWantsVegetables() { return true; }
		bool customerWantsCondiments() { return true; }
};
class ItalianHoagie : public Hoagie {
	private:
		list<string> meat {"salami", "pepperoni", "ham"};
		list<string> cheese {"provolone", "parmesan", "blue cheese"};
		list<string> veggies {"lettuce", "onion", "tomato"};
		list<string> conds {"salt", "pepper", "vinegar"};
	public:
		void addMeat()
		{	cout << "\tAdded meat! ";
			for(auto m : meat) cout << m << " ";
			cout << endl;
		}
		void addCheese()
		{	cout << "\tAdded cheese! ";
			for(auto c : cheese) cout << c << " ";
			cout << endl;
		}
		void addVegetables()
		{	cout << "\tAdded veggies! ";
			for(auto v : veggies) cout << v << " ";
			cout << endl;
		}
		void addCondiments()
		{	cout << "\tAdded condiments! ";
			for(auto c : conds) cout << c << " ";
			cout << endl;
		}
		//No hook overridden once they all remain true as implemented in superclass
};
class VeggieHoagie : public Hoagie {
	private:
		list<string> veggies {"lettuce", "onion", "tomato", "carrot", "beat"};
		list<string> conds {"salt", "pepper", "vinegar"};
	public:
		void addMeat() {} //must be overridden; in this case, empty cause it's not used
		void addCheese() {} //must be overridden; in this case, empty cause it's not used
		void addVegetables()
		{	cout << "\tAdded veggies! ";
			for(auto v : veggies) cout << v << " ";
			cout << endl;
		}
		void addCondiments()
		{	cout << "\tAdded condiments! ";
			for(auto c : conds) cout << c << " ";
			cout << endl;
		}
		//hooks being overridden once they changed content compared to superclass
		bool customerWantsMeat() { return false; }
		bool customerWantsCheese() { return false; }
};




int main() {

	Hoagie *toCust1 = new ItalianHoagie();
	cout << "Preparing Italian Hoagie for customer 1..." << endl;
	toCust1->makeSandwich();

	Hoagie *toCust2 = new VeggieHoagie();
	cout << "Preparing Veggie Hoagie for customer 2..." << endl;
	toCust2->makeSandwich();

	delete toCust1;
	delete toCust2;

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
