//============================================================================
// Name        : DP_Bridge.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Bridge Design Pattern in C++, Ansi-style
//============================================================================
//- Decouple an abstraction form its implementation so that the two can vary
//  independently (when you want to change abstract and concrete classes
//  independently)
//- It is poorly explained and everyone seems to explain it differently
//- By Derek Banas: Progressively add functionality while separating out major
//  differences using abstract classes
//Example:
//We have a remote control (abstract) that will implement control for electronic
//devices (abstract). Some buttons are common functions to all devices, for example
// buttons B7 and B8 for volume control. Other buttons are going to be implemented
//differently depending of the device: B5 and B6 will change channels for TVs,
//but will skip tracks for DVDs; B9 will follow this direction, muting TV and
//pausing DVD.
//
//     B7
//B5   B9    B6
//     B8
//
//So, the first abstract class (abstract electronic) defines the rules; The concrete
//class (electronic) adds extra rules; an abstract class (abstract remote) has a
//reference to the device and it defines abstract methods to be defined; finally, the
//concrete class (remote) defines the asbtract methods required.
//============================================================================

#include <iostream>
using namespace std;

//Implementer (implements buttons 7/8 for everyone; demands implementation of 5/6; it
//describes the functionalities of the device itself, not from the remote control)
class Device {
	protected:
		int deviceState = 0;	//current channel or track
		int maxState;			//max number allowed for channel or track (defined by device)
		int volumeSetting = 0;
		int maxVolume = 100;	//standard
	public:
		virtual ~Device() {}
		virtual void button5Pressed() = 0;	//channel or track down
		virtual void button6Pressed() = 0;	//channel or track up
		void button7Pressed()				//volume up
		{	volumeSetting += (volumeSetting<maxVolume ? 1 : 0);
			cout << "\tVolume up = " << volumeSetting << endl;
		}
		void button8Pressed()				//volume down
		{	volumeSetting -= (volumeSetting>0 ? 1 : 0);
			cout << "\tVolume down = " << volumeSetting << endl;
		}
		void deviceFeedback()				//print current status
		{ cout << "\tPlaying " << deviceState << " with volume " << volumeSetting << endl; }
};
//Concrete implementer (implements 5/6 for each device)
class TV : public Device {
	public:
		TV (int maxDState) { maxState = maxDState; }
		void button5Pressed()
		{	deviceState -= (deviceState>0 ? 1 : 0);
			cout << "\tChannel down = " << deviceState << endl;
		}
		void button6Pressed()
		{	deviceState += (deviceState<maxState ? 1 : 0);
			cout << "\tChannel up = " << deviceState << endl;
		}
};
//Concrete implementer (implements 5/6 for each device)
class DVD : public Device {
	public:
		DVD (int maxDState) { maxState = maxDState; }
		void button5Pressed()
		{	deviceState = (deviceState>0 ? --deviceState : maxState); //circular 1, 0, max, max-1...
			cout << "\tTrack down = " << deviceState << endl;
		}
		void button6Pressed()
		{	deviceState = (deviceState<maxState ? ++deviceState : 0); //circular max-1, max, 0, 1...
			cout << "\tTrack up = " << deviceState << endl;
		}
};


//Implements bridge for buttons 5/6/deviceFeedback; demands implementations of button 9
//(it bridges remote control with device functionalities, as well as it adds necessity
//of doing something with button 9)
class RemoteButton {
	private:
		Device *dev;
	public:
		RemoteButton (Device *d) : dev(d) {}
		virtual ~RemoteButton () {}
		void button5Pressed() { dev->button5Pressed(); } //bridging
		void button6Pressed() { dev->button6Pressed(); } //bridging
		void button7Pressed() { dev->button7Pressed(); } //bridging
		void button8Pressed() { dev->button8Pressed(); } //bridging
		void deviceFeedback() { dev->deviceFeedback(); } //bridging
		virtual void button9Pressed() = 0;
};
//Implements button 9 for TVs in cases it mutes/unmutes device
class TVRemoteMute : public RemoteButton {
	private:
		bool muteState = false;
	public:
		TVRemoteMute(Device *d) : RemoteButton(d) {}
		void button9Pressed() { muteState = !muteState; cout << (muteState ? "\tTV muted!" : "\tTV unmuted!") << endl;}
};
//Implements button 9 for TV in cases it pauses/resumes device
class TVRemotePause : public RemoteButton {
	private:
		bool pauseState = false;
	public:
		TVRemotePause(Device *d) : RemoteButton(d) {}
		void button9Pressed() { pauseState = !pauseState; cout << (pauseState ? "\tTV paused!" : "\tTV resumed!") << endl;}
};
//Implements button 9 for DVD pausing/resuming device
class DVDRemotePause : public RemoteButton {
	private:
		bool pauseState = false;
	public:
		DVDRemotePause(Device *d) : RemoteButton(d) {}
		void button9Pressed() { pauseState = !pauseState; cout << (pauseState ? "\tDVD paused!" : "\tDVD resumed!") << endl;}
};



int main() {

	RemoteButton *tv1 = new TVRemoteMute  (new TV(5));
	RemoteButton *tv2 = new TVRemotePause (new TV(4));
	RemoteButton *dvd = new DVDRemotePause(new DVD(10));

	cout << "Testing TV1..." << endl;
	tv1->button6Pressed();
	tv1->button6Pressed();
	tv1->button5Pressed();
	tv1->button5Pressed();
	tv1->button5Pressed();
	tv1->button9Pressed();
	tv1->button9Pressed();
	tv1->button7Pressed();
	tv1->button7Pressed();
	tv1->button8Pressed();
	tv1->deviceFeedback();

	cout << "Testing TV2..." << endl;
	tv2->button6Pressed();
	tv2->button6Pressed();
	tv2->button5Pressed();
	tv2->button5Pressed();
	tv2->button5Pressed();
	tv2->button9Pressed();
	tv2->button9Pressed();
	tv2->button7Pressed();
	tv2->button7Pressed();
	tv2->button8Pressed();
	tv2->deviceFeedback();

	cout << "Testing DVD..." << endl;
	dvd->button6Pressed();
	dvd->button6Pressed();
	dvd->button5Pressed();
	dvd->button5Pressed();
	dvd->button5Pressed();
	dvd->button5Pressed();
	dvd->button9Pressed();
	dvd->button9Pressed();
	dvd->button7Pressed();
	dvd->button7Pressed();
	dvd->button8Pressed();
	dvd->deviceFeedback();

	delete tv1;
	delete tv2;
	delete dvd;
	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
