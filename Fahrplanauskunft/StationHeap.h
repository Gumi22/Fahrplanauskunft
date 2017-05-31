#pragma once
#include "Station.h"

struct HeapItem {
	Station* Item;
	HeapItem* next;
	int weightedValue;
	Station* predecessor; //wird benutzt um nach hinten zu referenzieren :D 
	//TODO - umstiege mithilfe dieses Items erkennen????
};

class StationHeap
{
public:
	StationHeap();
	virtual ~StationHeap();
	void insertStationSorted(Station* newStation, int weightedValue, Station* previous);
	HeapItem* getNextStation();
	bool isEmpty();
private:
	HeapItem* root;
};

