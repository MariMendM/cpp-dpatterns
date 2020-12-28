//============================================================================
// Name        : DP_Strategy.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Design Pattern Strategy in C++, Ansi-style
//============================================================================
//STRATEGY PATTERN
//You use this pattern if you need to dynamically change an algorithm used by an object
//at run time. The pattern also allows you to eliminate code duplication. It separates
//behavior from super and subclasses. It is a super design pattern and is often the first
//one taught.
//It uses composition: its class fields are actually object themselves.
//============================================================================

#include <iostream>
#include <string>

using namespace std;

//----------------------------------------------------------------------------
//Consider following superclass and subclasses:

namespace Attempt1 {
	class Animal {
		private:
			string name;
			double height;
			string sound;
		public:
			Animal(string name) : name(name) { height = 0; sound = ""; };

			string getName(){ return name; }		void setName(string n){ name = n; }
			double getHeight(){ return height; }	void setHeight(double h){ height = (h>0 ? h : 0); }
			string getSound(){ return sound; }		void setSound(string s){ sound = s; }
	};

	class Dog : public Animal {
		public:
			Dog(string n) : Animal(n) { setSound("Bark"); }

			void digHole() { cout<< "Digging a hole!" << endl; }
	};

	class Bird : public Animal {
		public:
			Bird(string n) : Animal(n) { setSound("Chirp"); }
	};

	class Bat : public Animal {
		public:
			Bat(string n) : Animal(n) { setSound("What?"); }
	};
}

//Now, we need to provide for flying animals the capability to.. fly!
//We cannot simply add in superclass Animal a method that is not inherited by ALL of its subclasses;
//this would be a very bad solution, cause non-flying animal, such as Dog, would have to prevent the
//use of this inherited method somehow:

namespace Attempt2 {
	class Animal {
		private:
			string name;
			double height;
			string sound;
		public:
			Animal(string name) : name(name) { height = 0; sound = ""; };
			string getName(){ return name; }		void setName(string n){ name = n; }
			double getHeight(){ return height; }	void setHeight(double h){ height = (h>0 ? h : 0); }
			string getSound(){ return sound; }		void setSound(string s){ sound = s; }

			void fly() { cout << name << " flying!" << endl; } //DEMO OF A BAD BAAAD SOLUTION!
	};

	class Dog : public Animal {
		public:
			Dog(string n) : Animal(n) { setSound("Bark"); }
			void digHole() { cout<< "Digging a hole!" << endl; }

			void fly() { cout << "Ops! " << getName() << " cannot fly..." << endl; }  //DEMO OF A BAD BAAAD SOLUTION!
	};

	class Bird : public Animal {
		public:
			Bird(string n) : Animal(n) { setSound("Chirp"); }
	};

	class Bat : public Animal {
		public:
			Bat(string n) : Animal(n) { setSound("What?"); }
	};
}

//Another not good solution is to replicate code among all flying animals:

namespace Attempt3 {
	class Animal {
		private:
			string name;
			double height;
			string sound;
		public:
			Animal(string name) : name(name) { height = 0; sound = ""; };
			string getName(){ return name; }		void setName(string n){ name = n; }
			double getHeight(){ return height; }	void setHeight(double h){ height = (h>0 ? h : 0); }
			string getSound(){ return sound; }		void setSound(string s){ sound = s; }
	};

	class Dog : public Animal {
		public:
			Dog(string n) : Animal(n) { setSound("Bark"); }
			void digHole() { cout<< "Digging a hole!" << endl; }
	};

	class Bird : public Animal {
		public:
			Bird(string n) : Animal(n) { setSound("Chirp"); }
			void fly() { cout << getName() << " flying!" << endl; } //NOT SO NICE EITHER!
	};

	class Bat : public Animal {
		public:
			Bat(string n) : Animal(n) { setSound("What?"); }
			void fly() { cout << getName() << " flying!" << endl; } //NOT SO NICE EITHER!
	};
}

//No good solution so far! If we want to:
//- not duplicate code
//- keep class changes to force changes in other classes, not "breaking" inheritance
//we should use STRATEGY DESIGN PATTERN to solve the problem:

namespace Attempt4 {

	//PART OF SOLUTION: define a virtual class to define strategies to fly:
		class StrategyToFly {
			public:
				virtual ~StrategyToFly() {};
				virtual void fly() = 0;
		};
	//PART OF SOLUTION: derive the appropriate strategies
		class ItFlys : public StrategyToFly {
			public:
				void fly() { cout << "Flying!" << endl; }
		};
		class CannotFly : public StrategyToFly {
			public:
				void fly() { cout << "Ops! cannot fly..." << endl; }
		};

	class Animal {
		private:
			string name;
			double height;
			string sound;
			StrategyToFly *strat2fly; //PART OF SOLUTION: define an object to set which of the derived strategies is in use
		public:
			Animal(string name) : name(name)
			{ height = 0; sound = ""; strat2fly = new CannotFly(); } //PART OF SOLUTION: define one standard strategy (or not!)
			~Animal() { delete strat2fly; }
			string getName(){ return name; }		void setName(string n){ name = n; }
			double getHeight(){ return height; }	void setHeight(double h){ height = (h>0 ? h : 0); }
			string getSound(){ return sound; }		void setSound(string s){ sound = s; }

			StrategyToFly *getStratFly() { return strat2fly; }			//PART OF SOLUTION
			void setStratFly(StrategyToFly *stf) { strat2fly = stf; }	//PART OF SOLUTION
			void tryToFly() { strat2fly->fly(); }	//PART OF SOLUTION: execute the strategy currently set in 'strat2fly'
	};

	class Dog : public Animal {
		public:
			Dog(string n) : Animal(n)
			{	setSound("Bark");
				//setStratFly(new CannotFly()); //PART OF SOLUTION: initialize strategy for subclass (std already defined in Animal)
			}
			void digHole() { cout<< "Digging a hole!" << endl; }
	};

	class Bird : public Animal {
		public:
			Bird(string n) : Animal(n) {
				setSound("Chirp");
				setStratFly(new ItFlys());	//PART OF SOLUTION: initialize strategy for subclass
			}
	};

	class Bat : public Animal {
		public:
			Bat(string n) : Animal(n) {
				setSound("What?");
				setStratFly(new ItFlys());	//PART OF SOLUTION: initialize strategy for subclass
			}
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	{
		cout<< "Attempt1! ------" << endl;
		Attempt1::Bird tweety("Tweety");	tweety.getSound();
		Attempt1::Bat batty("Batty");
		Attempt1::Dog doggy("Doggy");		doggy.digHole();
	}

	{
		cout<< "Attempt2! ------" << endl;
		Attempt2::Bird tweety("Tweety");	tweety.fly();
		Attempt2::Bat batty("Batty");		batty.fly();
		Attempt2::Dog doggy("Doggy");		doggy.fly();
	}

	{
		cout<< "Attempt3! ------" << endl;
		Attempt3::Bird tweety("Tweety");	tweety.fly();
		Attempt3::Bat batty("Batty");		batty.fly();
		Attempt3::Dog doggy("Doggy");
	}

	{
		cout<< "Attempt4! ------" << endl;
		Attempt4::Bird tweety("Tweety");	tweety.tryToFly();
		Attempt4::Bat batty("Batty");		batty.tryToFly();
		Attempt4::Dog doggy("Doggy");		doggy.tryToFly();
		//Teaching doggy to fly...
		doggy.setStratFly(new Attempt4::ItFlys());
		doggy.tryToFly();
	}


	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
