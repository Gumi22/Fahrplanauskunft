#pragma once
#include "Station.h"

struct HeapItem {
	Station* Item;
	HeapItem* next;
	int weightedValue;
	Station* predecessor; //wird benutzt um nach hinten zu referenzieren :D 
	std::string line;
};

class StationHeap
{
public:
	StationHeap();
	virtual ~StationHeap();
	void insertStationSorted(Station* newStation, int weightedValue, Station* previous, std::string line);
	HeapItem* getNextStation();
	bool isEmpty();
	int getCount();
private:
	HeapItem* root;
	int Count;
};

