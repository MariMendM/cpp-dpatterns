//============================================================================
// Name        : DP_Adapter.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Adapter Design Pattern in C++, Ansi-style
//============================================================================
//- Allows two incompatible interfaces to work together;
//- Used when the client expects a (target) interface
//- The Adapter class allows the use of the available interface and the Target
//  interface
//- Any class can work together as long as the Adapter solves the issue that all
//  classes must implement every method defined by the shared interface
//============================================================================

#include <iostream>
using namespace std;

//Target
class EnemyAttacker {
	public:
		virtual ~EnemyAttacker () {}
		virtual void fireWeapon () = 0;
		virtual void driveForward () = 0;
		virtual void assignDriver (string name) = 0;
};
class EnemyTank : public EnemyAttacker {
	public:
		void fireWeapon ()   { cout << "\tCausing damage firing!" << endl; }
		void driveForward () { cout << "\tMoving by driving FWD!" << endl; }
		void assignDriver (string name) { cout << "\tDriver " << name << " in charge!" << endl; }
};

//Adaptee
class EnemyRobot {
	public:
		void smashWithHands () { cout << "\tCausing damage smashing with hands!" << endl; }
		void walkForward () { cout << "\tMoving by walking FWD!" << endl; }
		void reactToHuman (string name) { cout << "\tRobot tramps on " << name << "!" << endl; }
};

//Adapter
class EnemyRobotAdapter : public EnemyAttacker {
	private:
		EnemyRobot *eRobot;
	public:
		EnemyRobotAdapter () { eRobot = new EnemyRobot(); }
		~EnemyRobotAdapter () { delete eRobot; }
		void fireWeapon ()   { eRobot->smashWithHands(); }
		void driveForward () { eRobot->walkForward(); }
		void assignDriver (string name) { eRobot->reactToHuman(name); }
};


int main() {

	EnemyTank *tank = new EnemyTank();
	EnemyRobot *robot = new EnemyRobot();

	EnemyAttacker *robotAdapt = new EnemyRobotAdapter();

	cout << "Tank performing..." << endl;
	tank->assignDriver("Fulano");
	tank->driveForward();
	tank->fireWeapon();

	cout << "Robot performing..." << endl;
	robot->reactToHuman("Mari");
	robot->walkForward();
	robot->smashWithHands();

	cout << "Robot adpated performing..." << endl;
	robotAdapt->assignDriver("Marina");
	robotAdapt->driveForward();
	robotAdapt->fireWeapon();

	delete tank;
	delete robot;
	delete robotAdapt;


	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
