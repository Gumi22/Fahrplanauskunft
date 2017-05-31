#include "stdafx.h"
#include "Station.h"


Station::Station(std::string name)
{
	Connections = new std::vector<Connection*>;
	Visited = false;
	predecessor = nullptr;
	Name = name;
}


Station::~Station()
{
	while (Connections->size() != 0)
	{
		delete Connections->at(0);
		Connections->erase(Connections->begin());
	}
	Connections->clear();
	delete Connections;
}

//Fügt eine Verbindung zur Liste der Station hinzu:
void Station::addConnection(Station* other, std::string line, int distance) {
	if (other != nullptr) {
		Connection* temp = new Connection;
		temp->Distance = distance;
		temp->Line = line;
		temp->Next = other;
		Connections->push_back(temp);
	}
}

void Station::addConnectionBiDirectional(Station* other, std::string line, int distance) {
	addConnection(other, line, distance);
	if (other != nullptr) {
		other->addConnection(&*this, line, distance);
	}
}

Connection* Station::getConnection(int Num) {
	if (Num < Connections->size()) {
		return Connections->at(Num);
	}
	return nullptr;
}