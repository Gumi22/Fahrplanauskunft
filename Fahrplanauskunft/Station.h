#pragma once

#include <string>
#include <vector>

class Station;

struct Connection {
	Station* Next;
	int Distance;
	std::string Line;
	Connection* other;
};

class Station
{
public:
	Station();
	virtual ~Station();
	void addConnection(Station*, std::string, int);
	void addConnectionBiDirectional(Station*, std::string, int);
	Connection* getConnection(int Num); //Gibt den Pointer der angeforderten connection zurück, nullptr wenn nicht vorhanden
	std::string Name;
	bool Visited;
	Station* predecessor;

private:
	std::vector<Connection*>* Connections;
};


