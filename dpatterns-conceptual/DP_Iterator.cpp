//============================================================================
// Name        : DP_Iterator.cpp
// Author      : Mariane
// Version     :
// Copyright   : Your copyright notice
// Description : Iterator Design Pattern in C++, Ansi-style
//============================================================================
//- Provides you with a uniform way to access different collections of Objects
//- You can have an Array and a ArrayList and have an iterator for each treating
//  them the same (because they implement the same interface)
//============================================================================

#include <iostream>
#include <list>
#include <map>
#include <iomanip>
using namespace std;


//Without iterator design pattern: it works! But man, let's be serious... NO!

namespace Attempt1
{
	class SongInfo {
		private:
			string songName, bandName;
			int yearRelease;
		public:
			SongInfo() {} //Necessary to SongOf80s using built-in arrays (damn 80s!)
			SongInfo(string sn, string bn, int yr) : songName(sn), bandName(bn), yearRelease(yr) {}
			string getSongName() { return songName; }
			string getBandName() { return bandName; }
			int getYearRelease() { return yearRelease; }
	};

	//container list songs
	class SongsOf70 {
		private:
			list<SongInfo> bestSongs;
		public:
			SongsOf70() {
				addSong("Song 70 1","Beatles",1970);
				addSong("Song 70 2","Beatles",1973);
				addSong("Song 70 3","Gloria Gaynor",1978);
			}
			void addSong(string song, string band, int year) {
				SongInfo si = SongInfo(song,band,year);
				bestSongs.push_back(si);
			}
			list<SongInfo> getBestSongs() { return bestSongs; }
	};

	//built-in array bestSongs
	class SongsOf80 {
		private:
			SongInfo *bestSongs;
			int index = 0;
		public:
			SongsOf80() {
				bestSongs = new SongInfo[3];
				addSong("Song 80 1","A-HA",1981);
				addSong("Song 80 2","Depeche Mode",1985);
				addSong("Song 80 3","Boy George",1983);
			}
			void addSong(string song, string band, int year) {
				SongInfo si = SongInfo(song,band,year);
				bestSongs[index++] = si;
			}
			SongInfo *getBestSongs() { return bestSongs; }
	};

	//container multimap bestSongs
	class SongsOf90 {
		private:
			multimap<int,SongInfo> bestSongs;
			int index = 0;
		public:
			SongsOf90() {
				addSong("Song 90 1","Radiohead", 1993);
				addSong("Song 90 2","Offspring",1985);
				addSong("Song 90 3","Green Day",1983);
			}
			void addSong(string song, string band, int year) {
				SongInfo si = SongInfo(song,band,year);
				bestSongs.insert({index++, si});
			}
			multimap<int,SongInfo> getBestSongs() { return bestSongs; }
	};

	class DJ {
		private:
			SongsOf70 songs70;
			SongsOf80 songs80;
			SongsOf90 songs90;
		public:
			DJ(SongsOf70 s70, SongsOf80 s80, SongsOf90 s90) {
				songs70 = s70;
				songs80 = s80;
				songs90 = s90;
			}
			void showAllSongs ()
			{
				list<SongInfo> a70 = songs70.getBestSongs();
				SongInfo *a80 = songs80.getBestSongs();
				multimap<int,SongInfo> a90 = songs90.getBestSongs();

				cout << left <<  setw(12) << "Song Name" << setw(20) << "Band" << "Year" << endl;
				for (auto i : a70) cout << left << setw(12) << i.getSongName() << setw(20) << i.getBandName() << i.getYearRelease() << endl;
				for (int i=0; i<3; ++i) cout << left << setw(12) << a80[i].getSongName() << setw(20) << a80[i].getBandName() << a80[i].getYearRelease() << endl;
				for (auto i : a90) cout << left<< setw(12) << i.second.getSongName() << setw(20) << i.second.getBandName() << i.second.getYearRelease() << endl;
			}
	};

} //end namespace Attempt1



//Doing the right way!

namespace Attempt2
{
	//Forward declarations
	class SongIterator;
	class SongIteratorList;

	//Basic class to provide the type of data to store songs
	class SongInfo {
		private:
			string songName, bandName;
			int yearRelease;
		public:
			SongInfo() {} //Necessary to SongOf80s using built-in arrays (damn 80s!)
			SongInfo(string sn, string bn, int yr) : songName(sn), bandName(bn), yearRelease(yr) {}
			string getSongName() { return songName; }
			string getBandName() { return bandName; }
			int getYearRelease() { return yearRelease; }
	};

	//Class to store SongInfo form 70's (uses container <list>)
	class SongsOf70 {
		private:
			list<SongInfo> bestSongs;
		public:
			SongsOf70() {
				addSong("Song 70 1","Beatles",1970);
				addSong("Song 70 2","Rolling Stones",1973);
				addSong("Song 70 3","Gloria Gaynor",1978);
			}
			void addSong(string song, string band, int year) {
				SongInfo si = SongInfo(song,band,year);
				bestSongs.push_back(si);
			}

			//Functions to ITERATOR
			SongIterator *createIterator();
			int getBegin() { return 0; }
			int getEnd()   { return bestSongs.size(); }
			SongInfo getElementAt(int i)
			{	auto iter = bestSongs.begin();
				for(int qtd=0; qtd<i; qtd++)
					iter++;
				return *iter;
			}
	};

	//Class to store SongInfo form 70's (uses built-in array)
	class SongsOf80 {
		private:
			SongInfo *bestSongs;
			int index = 0;
		public:
			SongsOf80() {
				bestSongs = new SongInfo[3]; //Fixed for laziness! arrays are not the focus here!
				addSong("Song 80 1","A-HA",1981);
				addSong("Song 80 2","Depeche Mode",1985);
				addSong("Song 80 3","Boy George",1983);
			}
			void addSong(string song, string band, int year) {
				SongInfo si = SongInfo(song,band,year);
				bestSongs[index++] = si;
			}

			//Functions to ITERATOR
			SongIterator *createIterator();
			int getBegin() { return 0; }
			int getEnd()   { return 3; } //shall be implemented if not fixed
			SongInfo getElementAt(int i) { return bestSongs[i]; }
	};

	//Class to store SongInfo form 70's (uses container <multimap>)
	class SongsOf90 { //: public SongIterator {
		private:
			multimap<int,SongInfo> bestSongs;
			int index = 0;
		public:
			SongsOf90() {
				addSong("Song 90 1","Radiohead", 1993);
				addSong("Song 90 2","Offspring",1995);
				addSong("Song 90 3","Green Day",1998);
				addSong("Song 90 4","REM",1993);
			}
			void addSong(string song, string band, int year) {
				SongInfo si = SongInfo(song,band,year);
				bestSongs.insert({index++, si});
			}

			//Functions to ITERATOR
			SongIterator *createIterator();
			int getBegin() { return 0; }
			int getEnd()   { return bestSongs.size(); }
			SongInfo getElementAt(int i)
			{	auto iter = bestSongs.begin();
				for(int qtd=0; qtd<i; qtd++)
					iter++;
				return iter->second;
			}
	};

	//Class to implement common Iterators for all 'SongsOfXX' classes
	class SongIterator {
		public:
			virtual ~SongIterator () {}
			virtual int getBegin() = 0;
			virtual int getEnd() = 0;
			virtual SongInfo getElementAt(int i) = 0;
	};
	class SongIteratorList : public SongIterator {
		private:
			SongsOf70 *songs70;
		public:
			SongIteratorList(SongsOf70 *s70) { songs70 = s70;}
			int getBegin() { return songs70->getBegin(); }
			int getEnd()   { return songs70->getEnd();   }
			SongInfo getElementAt(int i) { return songs70->getElementAt(i); }
	};
	class SongIteratorBuiltInArray : public SongIterator {
		private:
			SongsOf80 *songs80;
		public:
			SongIteratorBuiltInArray(SongsOf80 *s80) { songs80 = s80;}
			int getBegin() { return songs80->getBegin(); }
			int getEnd()   { return songs80->getEnd();   }
			SongInfo getElementAt(int i) { return songs80->getElementAt(i); }
	};
	class SongIteratorMultimap : public SongIterator {
		private:
			SongsOf90 *songs90;
		public:
			SongIteratorMultimap(SongsOf90 *s90) { songs90 = s90;}
			int getBegin() { return songs90->getBegin(); }
			int getEnd()   { return songs90->getEnd();   }
			SongInfo getElementAt(int i) { return songs90->getElementAt(i); }
	};


	class DJ {
		private:
			SongsOf70 songs70;
			SongsOf80 songs80;
			SongsOf90 songs90;
		public:
			DJ(SongsOf70 s70, SongsOf80 s80, SongsOf90 s90) : songs70(s70), songs80(s80), songs90(s90) {}
			void showAllSongs ()
			{
				cout << left <<  setw(12) << "Song Name" << setw(20) << "Band" << "Year" << endl;
				for (int i=songs70.getBegin(); i<songs70.getEnd(); i++)
					cout << left << setw(12) << songs70.getElementAt(i).getSongName() << setw(20) << songs70.getElementAt(i).getBandName() << songs70.getElementAt(i).getYearRelease() << endl;
				for (int i=songs80.getBegin(); i<songs80.getEnd(); i++)
					cout << left << setw(12) << songs80.getElementAt(i).getSongName() << setw(20) << songs80.getElementAt(i).getBandName() << songs80.getElementAt(i).getYearRelease() << endl;
				for (int i=songs90.getBegin(); i<songs90.getEnd(); i++)
					cout << left << setw(12) << songs90.getElementAt(i).getSongName() << setw(20) << songs90.getElementAt(i).getBandName() << songs90.getElementAt(i).getYearRelease() << endl;
			}
	};

	//Shall be implemented outisde class due to forward declaration
	SongIterator *SongsOf70::createIterator() { return new SongIteratorList(this); }
	SongIterator *SongsOf80::createIterator() { return new SongIteratorBuiltInArray(this); }
	SongIterator *SongsOf90::createIterator() { return new SongIteratorMultimap(this); }

} //end namespace Attempt2


int main() {

	{
		cout << "Attempt1 ---------------------------------\n";
		Attempt1::SongsOf70 songs70;
		Attempt1::SongsOf80 songs80;
		Attempt1::SongsOf90 songs90;

		Attempt1::DJ dj(songs70, songs80, songs90);
		dj.showAllSongs();
	}

	{
		cout << "Attempt2 ---------------------------------\n";
		Attempt2::SongsOf70 songs70;
		Attempt2::SongsOf80 songs80;
		Attempt2::SongsOf90 songs90;

		Attempt2::DJ dj(songs70, songs80, songs90);
		dj.showAllSongs();
	}
	cout << "END OF PROGRAM" << endl; // prints END OF PROGRAM
	return 0;
}
