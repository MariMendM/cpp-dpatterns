//============================================================================
// Name        : DP_Builder.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Builder Design Pattern in C++, Ansi-style
//============================================================================
//Used when:
//- you want to create objects made of a bunch of other objects;
//- you want the creation of these parts to be independent from the main object
//- you want to hide the creation of the parts from the client so both aren't
//  dependent
//- the builder knows the specifics and nobody else does
//============================================================================

#include <iostream>
using namespace std;

class RobotPlan {
	public:
		virtual ~RobotPlan() {}
		virtual void setRobotHead (string h) = 0;
		virtual void setRobotTorso(string t) = 0;
		virtual void setRobotArms (string a) = 0;
		virtual void setRobotLegs (string l) = 0;
};
class Robot : public RobotPlan {
	private:
		string robotHead, robotTorso, robotArms, robotLegs = "";
	public:
		void setRobotHead (string h) { robotHead = h; }
		void setRobotTorso(string t) { robotTorso = t;}
		void setRobotArms (string a) { robotArms = a; }
		void setRobotLegs (string l) { robotLegs = l; }
		string getRobotHead () { return robotHead; }
		string getRobotTorso() { return robotTorso;}
		string getRobotArms () { return robotArms; }
		string getRobotLegs () { return robotLegs; }
};


//classes that contain the blueprint to build the robot
class RobotBuilder {
	public:
		virtual ~RobotBuilder () {}
		virtual void buildRobotHead () = 0;
		virtual void buildRobotTorso() = 0;
		virtual void buildRobotArms () = 0;
		virtual void buildRobotLegs () = 0;
		virtual Robot *getRobot() = 0;
};
class OldRobotBuilder : public RobotBuilder {
	private:
		Robot *robot;
	public:
		OldRobotBuilder ()		{ robot = new Robot(); }
		void buildRobotHead ()	{ robot->setRobotHead("Tin Head"); }
		void buildRobotTorso()	{ robot->setRobotTorso("Tin Torso"); }
		void buildRobotArms ()	{ robot->setRobotArms("Spring Arms"); }
		void buildRobotLegs ()	{ robot->setRobotLegs("Tin Legs"); }
		Robot *getRobot() 		{ return robot; }
};

//class that receives specification 'RobotBuilder' of the robot
//and demands its creation using 'makeRobot', delivering the created
//robot using 'getRobot'
class RobotEngineer { //very used in literature as 'director'
	private:
		RobotBuilder *robotBuilder;
	public:
		RobotEngineer(RobotBuilder *robot) { robotBuilder = robot; }
		Robot *getRobot() { return robotBuilder->getRobot(); }
		void makeRobot () {
			robotBuilder->buildRobotHead();
			robotBuilder->buildRobotTorso();
			robotBuilder->buildRobotArms();
			robotBuilder->buildRobotLegs();
		}
};


int main() {

	//creating the "blueprint" to my new robot...
	RobotBuilder *oldStyleRobot = new OldRobotBuilder();

	//passing the OldRobotBuilder specification of creation to the engineer...
	RobotEngineer *robotEngineer = new RobotEngineer(oldStyleRobot);

	//telling the engineer to create the robot using specification passed
	robotEngineer->makeRobot();

	//now, we get our newly built robot!
	Robot *robot1 = robotEngineer->getRobot();

	cout << "My robot has " << robot1->getRobotHead() << ", " \
							<< robot1->getRobotTorso() << ", " \
							<< robot1->getRobotArms() << ", " \
							<< robot1->getRobotLegs() << endl;

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
