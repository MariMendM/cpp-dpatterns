//============================================================================
// Name        : DP_Observer.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Observer Design Pattern in C++, Ansi-style
//============================================================================
//OBSERVER DESIGN PATTERN
//Used when many other objects need an update when other object changes. For example,
//we have a subject (publisher) object that represents thousands of individual stocks
//in the Stock Market and we need to send updates to multiple observers (subscribers).

//Benefit: Publisher doesn't need to know anything about the subscribers
//Negative: Publisher may send updates that don't matter to subscribers
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------
//class Subject declares objects of class Observer
//class Observer declares objects of class Subject
//For that, we are forwarding declaring Subject in ways that Observers will trust it exists
class Subject;
//-------------------------------------------------------------

//-------------------------------------------------------------
//ATTENTION: interfaces and implementations are separated because using forward declaration,
//the compiler complains that 'incomplete classes' are being used if implementation is
//inside class interface
//-------------------------------------------------------------

//-------------------------------------------------------------
//OBSERVER AND STOCK OBSERVER INTERFACES
//-------------------------------------------------------------
class Observer{
	public:
		virtual ~Observer() {}
		virtual void update(double ibmPrice, double aaplPrice, double googPrice) = 0;
};
class StockObserver : public Observer{
	private:
		double ibmPrice, aaplPrice, googPrice;
		static int observerIDTracker;
		int observerID;
		Subject *stockGrabber;
	public:
		StockObserver(Subject *stckGrab);
		void update(double ibmPrice, double aaplPrice, double googPrice);
		void printPrices();
};

//-------------------------------------------------------------
//SUBJECT AND STOCK GRABBER INTERFACES
//-------------------------------------------------------------
class Subject {
	public:
		virtual ~Subject() {}
		virtual void procRegister (Observer *o) = 0;
		virtual void procUnregister (Observer *o) = 0;
		virtual void notifyObserver() = 0;
};
class StockGrabber : public Subject {
	private:
		vector<Observer *> observers;
		double ibmPrice, aaplPrice, googPrice;
	public:
		void procRegister(Observer *o);
		void procUnregister(Observer *o);
		void notifyObserver();
		void setIBMPrice (double p);
		void setAAPLPrice (double p);
		void setGOOGPrice (double p);
};

//--------------------------------------------------------------
//STOCK OBSERVER IMPLEMENTATION
//--------------------------------------------------------------
int StockObserver::observerIDTracker = 0;

StockObserver::StockObserver(Subject *stckGrab) {
	ibmPrice = aaplPrice = googPrice = 0;
	stockGrabber = stckGrab;
	observerID = ++observerIDTracker;
	cout << "\tNew Observer " << observerID << " registered in stockGrabber" << endl;
	stockGrabber->procRegister(this);
}
void StockObserver::update(double ibmPrice, double aaplPrice, double googPrice) {
	this->ibmPrice = ibmPrice;
	this->aaplPrice = aaplPrice;
	this->googPrice = googPrice;
	printPrices();
}
void StockObserver::printPrices() {
	cout << "\tObs ID " << observerID << ": IBM<" << ibmPrice << ">; APPLE<" << aaplPrice << ">; GOOGLE<" << googPrice << ">;" << endl;
}

//--------------------------------------------------------------
//STOCK GRABBER IMPLEMENTATION
//--------------------------------------------------------------
void StockGrabber::procRegister(Observer *o) { observers.push_back(o); }
void StockGrabber::procUnregister(Observer *o) {
	auto iterO = find(observers.begin(),observers.end(), o);
	if (iterO != observers.end())
		observers.erase(iterO);
}
void StockGrabber::notifyObserver() {
	for (auto obs : observers)
		obs->update(ibmPrice, aaplPrice, googPrice);
}
void StockGrabber::setIBMPrice (double p)  { ibmPrice = p; notifyObserver(); }
void StockGrabber::setAAPLPrice (double p) { aaplPrice = p; notifyObserver(); }
void StockGrabber::setGOOGPrice (double p) { googPrice = p; notifyObserver(); }

//--------------------------------------------------------------

int main() {

	StockGrabber *sGrabb = new StockGrabber();

	cout << "Adding observer 1..." << endl;
	StockObserver *sObs1 = new StockObserver(sGrabb);
	sObs1->printPrices();

	cout << "Adding observer 2..." << endl;
	StockObserver *sObs2 = new StockObserver(sGrabb);
	sObs2->printPrices();

	cout << "Changing stock prices..." << endl;
	sGrabb->setIBMPrice(197.5);
	sGrabb->setAAPLPrice(291.7);
	sGrabb->setGOOGPrice(254.3);

	cout << "Adding observer 3..." << endl;
	StockObserver *sObs3 = new StockObserver(sGrabb);
	sObs3->printPrices();

	cout << "Changing IBM stock prices..." << endl;
	sGrabb->setIBMPrice(97.5);

	cout << "Removing observer 2..." << endl;
	sGrabb->procUnregister(sObs2);

	cout << "Changing IBM stock prices..." << endl;
	sGrabb->setIBMPrice(312.9);

	delete sGrabb;
	delete sObs1;
	delete sObs2;
	delete sObs3;

	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
