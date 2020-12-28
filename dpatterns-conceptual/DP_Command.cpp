//============================================================================
// Name        : DP_Command.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Command Design Pattern in C++, Ansi-style
//============================================================================
//- An object is used to represent and encapsulate all the information needed
//  to call a method at a later time
//- This info includes the method name, the object that owns the method and
//  values for the method parameters
//- It allows to store lists of code that is executed at a later time or many
//  times
//- Client says I want a specific command to run when execute() is called on
//  one of these encapsulated (hidden) objects
//- An object called invoker transfers this command to another object called
//  receiver to execute the right code
//============================================================================

#include <iostream>
#include <list>
using namespace std;

class ElectronicDevice {
	public:
		virtual ~ElectronicDevice () {}
		virtual void on() = 0;
		virtual void off() = 0;
		virtual void volumeUp() = 0;
		virtual void volumeDown() = 0;
};
class Television : public ElectronicDevice {
	private:
		int volume = 0;
	public:
		virtual void on() { cout << "\tTV is on!" << endl; }
		virtual void off() { cout << "\tTV is off!" << endl;}
		virtual void volumeUp() { cout << "\tVolume = " << (volume<10 ? ++volume : volume) << endl; }
		virtual void volumeDown() { cout << "\tVolume = " << (volume>0 ? --volume : volume) << endl; }
};
class Radio : public ElectronicDevice {
	private:
		int volume = 0;
	public:
		virtual void on() { cout << "\tRadio is on!" << endl; }
		virtual void off() { cout << "\tRadio is off!" << endl;}
		virtual void volumeUp() { cout << "\tVolume = " << (volume<10 ? ++volume : volume) << endl; }
		virtual void volumeDown() { cout << "\tVolume = " << (volume>0 ? --volume : volume) << endl; }
};


class Command {
	public:
		virtual ~Command() {}
		virtual void execute() = 0;
		virtual void undo() = 0;
};
class TurnTVOn : public Command {
	private:
		ElectronicDevice * device;
	public:
		TurnTVOn(ElectronicDevice *dev) : device(dev) {}
		void execute() { device->on(); }
		void undo() {}
};
class TurnTVOff : public Command {
	private:
		ElectronicDevice * device;
	public:
		TurnTVOff(ElectronicDevice *dev) : device(dev) {}
		void execute() { device->off(); }
		void undo() {}
};
class TurnTVUp : public Command {
	private:
		ElectronicDevice * device;
	public:
		TurnTVUp(ElectronicDevice *dev) : device(dev) {}
		void execute() { device->volumeUp(); }
		void undo() { device->volumeDown(); }
};
class TurnTVDown : public Command {
	private:
		ElectronicDevice * device;
	public:
		TurnTVDown(ElectronicDevice *dev) : device(dev) {}
		void execute() { device->volumeDown(); }
		void undo() { device->volumeUp(); }
};
class TurnItAllOff : public Command {
	private:
		list<ElectronicDevice *> devices;
	public:
		TurnItAllOff(list<ElectronicDevice *> listDev) : devices(listDev) {}
		void execute() { for (auto dev : devices) dev->off(); }
		void undo() {}
};


//Invoker
class DeviceButton {
	private:
		Command *cmd;
	public:
		DeviceButton (Command *c) : cmd(c) {}
		void press() { cmd->execute(); }
		void pressUndo() { cmd->undo(); }
};

class TVRemote{
	public:
		static ElectronicDevice *getDevice() { return new Television();}
};


int main() {

	TVRemote *tv = new TVRemote();
	ElectronicDevice *dev = tv->getDevice();

	cout << "Turning TV on..." << endl;
	TurnTVOn *cmdON = new TurnTVOn(dev);
	DeviceButton *onPressed = new DeviceButton(cmdON);
	onPressed->press();
	delete cmdON;
	delete onPressed;

	cout << "Turning TV volume up..." << endl;
	TurnTVUp *cmdUP = new TurnTVUp(dev);
	onPressed = new DeviceButton(cmdUP);
	onPressed->press();
	onPressed->press();
	onPressed->press();
	onPressed->press();
	cout << "Turning TV volume up using undo..." << endl;
	onPressed->pressUndo();
	delete cmdUP;
	delete onPressed;

	cout << "Turning all devices off..." << endl;
	list<ElectronicDevice *> devices;
	devices.push_back(new Radio());
	devices.push_back(new Television());
	TurnItAllOff *cmdTIAO = new TurnItAllOff(devices);
	onPressed = new DeviceButton(cmdTIAO);
	onPressed->press();
	delete cmdTIAO;

	delete tv;
	delete dev;


	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}


