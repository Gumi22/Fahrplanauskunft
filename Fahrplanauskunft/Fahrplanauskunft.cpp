// Fahrplanauskunft.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include "Station.h"
#include "StationHeap.h"

using namespace std;

bool FindShortestPath(string From, string To);
Station* getStation(string Name);
Station* Dijkstra(Station* StartStation, Station* GoalStation);
void printPath(Station* EndStation);
void buildGraphFromFile(string Filename);

unordered_map <string, Station*>* Stations;
int minweg;

int main()
{
    //Hashmap die später alle Stationen halten soll:
	Stations = new unordered_map <string, Station*>;
	minweg = 0;

	//Einlesen der Datei:
	string Filename;
	cout << "Dateiname: ";
	cin >> Filename;

	//Erstellen des Graphen:
	buildGraphFromFile(Filename);
	
	//Fragen nach demm Start und Ziel
	string Start, Goal;
	cin >> Start >> Goal;
	if (!FindShortestPath(Start, Goal)) {
		cout << "Es wurde keine Verbindung gefunden";
	}
	return 0;
}

//Findet den kürzesten Weg vom Start zum Ziel und gibt zurück ob die Suche erfolgreich war.
bool FindShortestPath(string Start, string Goal) {
	Station* StartStation = getStation(Start);
	Station* GoalStation = getStation(Goal);
	if (StartStation != nullptr && GoalStation != nullptr) {
		//Dijkstra:
		Station* temp = Dijkstra(StartStation, GoalStation);
		if (temp == GoalStation) {
			//Ziel wurde gefunden und es war verbunden mit dem Start, gib die Strecke aus:
			printPath(temp);
			return true;
		}
	}
	return false;
}

//Gibt die Station aus der Hashtable zurück. Falls keine Existiert wird ein nullptr zurückgegeben.
Station* getStation(string Name) {
	//So fängt man ab ob es schon existiert, oder nicht:
	try {
		Station* test = Stations->at("test");
		return test;
	}
	catch (exception& e) {
		return nullptr;
	}
}

//Wendet den Dijkstra-Algorythmus an und gibt dann das Ziel zurück, indem der Vorgängerknoten steht.
Station* Dijkstra(Station* StartStation, Station* GoalStation) {
	int minDist = 0;
	//Die Suche geht von Ziel zu start um am Schluss die Vorgänger in richtiger Reihenfolge ausgeben zu können :D

	StationHeap* Heap = new StationHeap();
	do {
		GoalStation->Visited = true; // Knoten als besucht markieren

		//Alle Verbindungen des Knotens in den Heap einfügen, die noch nicht besucht wurden
		int i = 0;
		Connection* temp = GoalStation->getConnection[i];
		while (temp != nullptr) {
			if (!temp->Next->Visited) {
				//TODO: auf Umstiege überprüfen!!!! und mindist dementsprechend ändern :D
				Heap->insertStationSorted(temp->Next, temp->Distance + minDist);
			}
			i++;
		}

		do {
			// Knoten mit minimalem Gewicht aus Heap entfernen, minweg aktualisieren
			HeapItem* temp = Heap->getNextStation();
			GoalStation = temp->Item;
			minDist = temp->weightedValue;
		} while (GoalStation->Visited);

	} while (GoalStation != StartStation && !Heap->isEmpty()); // Solange Zielknoten nicht erreicht
	minweg = minDist;
	StartStation->predecessor = GoalStation;
	return StartStation;
}

//Gibt die Vorgänger der Stationen aus...muss noch umgedreht und überarbeitet werden (derzeit von hinten nach vorne und ohne Gesamtzeit)
//...gelöst durch von Hinten nach Vorne durchschauen des Ziels im Dijkstra
void printPath(Station* EndStation) {

	do{
		cout << EndStation->Name << " - ";
	} while (EndStation->predecessor != nullptr);
	cout << "135 min";
}

void buildGraphFromFile(string Filename) {
	ifstream infile(Filename);
	string line = "";
	string connLine = ""; //Wird für den Namen der Verbindung benutzt
	string temp = ""; //Wird benutzt um die Stationsnamen einzulesen
	int tempDist = 0; //Wird benutzt um die Entfernungen zwischenzuspeichern
	while (getline(infile, line)) { //Jede Zeile bearbeiten
		stringstream ss(line); 
		getline(ss, connLine, ':'); //in connLine steht nun der Name der Ubahnlinie
		getline(ss, temp, '"'); //Gehe zur ersten Station
		while (!ss.eof) {
			getline(ss, temp, '"'); //in temp steht nun der Name der Station

			//TODO: Fertig schreiben !!!!!!!

			if (getStation(temp) == nullptr) { //Station noch nicht vorhanden neue Station erzeigen

			}
			else {

			}

			getline(ss, temp, '"'); //gehe zum nächsten " -> also zur nächsten Station
		}
	}
}