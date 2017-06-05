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

unordered_map <string, Station*> Stations; //Hashmap, die alle Stationen enthält :D
int minweg;

int main()
{
	minweg = 0;

	//Einlesen der Datei:
	string Filename;
	cout << "Dateiname: ";
	cin >> Filename;

	//Erstellen des Graphen:
	buildGraphFromFile(Filename);
	
	//Fragen nach demm Start und Ziel
	cout << "Start Ziel eingeben: " << endl;
	string Start, Goal;
	cin >> Start >> Goal;
	if (!FindShortestPath(Start, Goal)) {
		cout << "Es wurde keine Verbindung gefunden";
	}

	cin >> Start;
	return 0;
}

//Findet den kürzesten Weg vom Start zum Ziel und gibt zurück ob die Suche erfolgreich war.
bool FindShortestPath(string Start, string Goal) {
	Station* StartStation = getStation(Start);
	Station* GoalStation = getStation(Goal);
	if (StartStation != nullptr && GoalStation != nullptr) {
		//Dijkstra:
		cout << "Start und Ziel gefunden, beginne Berechnung: " << endl;
		Station* temp = Dijkstra(StartStation, GoalStation);
		if (temp == StartStation) {
			//Ziel wurde gefunden und es war verbunden mit dem Start, gib die Strecke aus:
			cout << "Kuerzester Weg: " << minweg << " Minuten :D" << endl;
			printPath(StartStation);
			return true;
		}
	}
	return false;
}

//Gibt die Station aus der Hashtable zurück. Falls keine Existiert wird ein nullptr zurückgegeben.
Station* getStation(string Name) {
	//So fängt man ab ob es schon existiert, oder nicht:
	try {
		Station* test = Stations.at(Name);
		return test;
	}
	catch (exception& e) {
		return nullptr;
	}
}

//Wendet den Dijkstra-Algorythmus an und gibt dann das Ziel zurück, indem der Vorgängerknoten steht.
Station* Dijkstra(Station* StartStation, Station* GoalStation) {
	int minDist = 0;
	int maxCount = 0;
	//Die Suche geht von Ziel zu start um am Schluss die Vorgänger in richtiger Reihenfolge ausgeben zu können :D
	HeapItem * current = nullptr;
	HeapItem * last = nullptr;
	StationHeap* Heap = new StationHeap();
	do {
		GoalStation->Visited = true; // Knoten als besucht markieren
		//Alle Verbindungen des aktuellen Knotens in den Heap einfügen, die noch nicht besucht wurden
		int i = 0;
		Connection* temp = GoalStation->getConnection(i);
		while (temp != nullptr) {
			temp = GoalStation->getConnection(i);
			if (!temp->Next->Visited) {

				//TODO: auf Umstiege überprüfen!!!! und mindist dementsprechend ändern :D

				Heap->insertStationSorted(temp->Next, temp->Distance + minDist, GoalStation);
				int d = Heap->getCount();
				if (d > maxCount) {
					maxCount = d;
				}
			}
			i++;
			temp = GoalStation->getConnection(i);
		}
		//Station* temp2 = GoalStation;
		do {
			// Knoten mit minimalem Gewicht aus Heap entfernen, minweg aktualisieren und predecessor aktualisieren
			HeapItem* temph = Heap->getNextStation();
			temph->Item->predecessor = temph->predecessor; 
			GoalStation = temph->Item; 
			minDist = temph->weightedValue;
		} while (GoalStation->Visited);
		//cout << GoalStation->Name << " " << GoalStation->predecessor->Name << endl;

	} while (GoalStation != StartStation ); // Solange Zielknoten nicht erreicht
	minweg = minDist;
	cout << "Maximale Heapgröße" << maxCount << endl;
	return StartStation;
}

//Gibt die Vorgänger der Stationen aus...muss noch umgedreht und überarbeitet werden (derzeit von hinten nach vorne und ohne Gesamtzeit)
//...gelöst durch von Hinten nach Vorne durchschauen des Ziels im Dijkstra
void printPath(Station* EndStation) {
	Station* temp = EndStation;
	while (temp != nullptr && temp->predecessor != nullptr && temp->Name != temp->predecessor->Name) {
		cout << temp->Name << " - ";
		temp = temp->predecessor;
	}
	cout << temp->Name;
}

void buildGraphFromFile(string Filename) {
	ifstream infile(Filename);
	string line = "";
	string connLine = ""; //Wird für den Namen der Verbindung benutzt
	string temp = ""; //Wird benutzt um die Stationsnamen einzulesen
	int tempDist = 0; //Wird benutzt um die Entfernungen zwischenzuspeichern
	Station* actual = nullptr;
	Station* last = nullptr;

	while (getline(infile, line)) { //Jede Zeile bearbeiten
		stringstream ss(line); 
		getline(ss, connLine, ':'); //in connLine steht nun der Name der Ubahnlinie
		getline(ss, temp, '"'); //Gehe zur ersten Station

		while (!ss.eof()) {
			getline(ss, temp, '"'); //in temp steht nun der Name der Station			

			if (getStation(temp) == nullptr) { //Station noch nicht vorhanden neue Station erzeugen und speichern
				actual = new Station(temp);
				Stations[temp] = actual;
				//cout << actual->Name;
			}
			actual = Stations[temp];
			actual->addConnectionBiDirectional(last, connLine, tempDist);

			ss >> tempDist; //in tempDist steht nun die Distanz zur nächsten Station
			last = actual;
			getline(ss, temp, '"'); //gehe zum nächsten ' " ' -> also zur nächsten Station (bzw zum eof falls keine Station mehr vorhanden?).
		}
		last = nullptr; // Die Linien sollten nicht verbunden werden
	}
}