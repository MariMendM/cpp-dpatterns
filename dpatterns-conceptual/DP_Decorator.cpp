//============================================================================
// Name        : DP_Decorator.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//- Allow to modify an object dynamically
//- Used when you want the capabilities of inheritance with subclasses, but you
//  need to add functionality at runtime
//- It is more flexible than inheritance
//- Simplifies code because you add functionality using many simple classes
//- Rather than rewrite old code you can extend with new code
//============================================================================

#include <iostream>
using namespace std;

//Let's say we have a pizza shop and we need very easy to add tops in the pizzas
//as well as print the costs in receipt

//First possibility, creating thousand of subclasses to describe each pizza/cost
//and editing each one every time the price of flour rise up once it is something
//static! Not necessary to say that this is definitely NOT the right way to do it...

namespace Attemp1 {

	class Pizza {
		public:
			virtual ~Pizza() {}
			virtual string getDescription () = 0;
			virtual double getCost() = 0;
	};
	class ThreeCheesePizza : public Pizza {
		private:
			string description = "Thin Dough, Mozzarela, BlueCheese, Parmesan";
			double cost = 10.0;
		public:
			string getDescription () { return description; }
			double getCost() { return cost; }
	};
} //end namespace Attempt1



//The right way of doing it: using Decorator DP!

namespace Attempt2 {

	class Pizza {
		public:
			virtual ~Pizza() {}
			virtual string getDescription () = 0;
			virtual double getCost() = 0;
	};
	class PlainPizza : public Pizza {
		//private:
			//string description = "Thin Dough";
			//double cost = 4.0;
		public:
			PlainPizza () { cout << "Adding dough" << endl; }
			string getDescription () { return "Thin Dough"; }
			double getCost() { return 4.00; }
	};

	class ToppingDecorator : public Pizza {
		protected:
			Pizza *tempPizza;
		public:
			ToppingDecorator (Pizza *p) : tempPizza(p) { }
			string getDescription() { return tempPizza->getDescription(); }
			double getCost() { return tempPizza->getCost(); }

	};

	class Mozzarella : public ToppingDecorator {
		public:
			Mozzarella (Pizza *p) : ToppingDecorator(p) { cout << "Adding mozzarella" << endl; }
			string getDescription() { return tempPizza->getDescription() + ", Mozzarella"; }
			double getCost() { return tempPizza->getCost() + 1.50; }
	};

	class TomatoSauce : public ToppingDecorator {
		public:
			TomatoSauce (Pizza *p) : ToppingDecorator(p) { cout << "Adding tomato sauce" << endl; }
			string getDescription() { return tempPizza->getDescription() + ", Tomato Sauce"; }
			double getCost() { return tempPizza->getCost() + 0.80; }
	};

} //end namespace Attempt2


int main() {

	Attempt2::Pizza *pizza1 = new Attempt2::TomatoSauce(new Attempt2::Mozzarella (new Attempt2::PlainPizza()));

	cout << "Order pizza1:" << endl;
	cout << "\tDescription = " << pizza1->getDescription() << endl;;
	cout << "\tCoast = " << pizza1->getCost() << endl;;

	Attempt2::Pizza *pizza2 = new Attempt2::TomatoSauce(new Attempt2::PlainPizza());

	cout << "Order pizza2:" << endl;
	cout << "\tDescription = " << pizza2->getDescription() << endl;;
	cout << "\tCoast = " << pizza2->getCost() << endl;;

	delete pizza1;
	delete pizza2;
	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
