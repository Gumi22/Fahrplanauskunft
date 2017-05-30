#pragma once
#include "Station.h"

struct HeapItem {
	Station* Item;
	HeapItem* next;
	int weightedValue;
};

class StationHeap
{
public:
	StationHeap();
	virtual ~StationHeap();
	void insertStationSorted(Station* newStation, int weightedValue);
	HeapItem* getNextStation();
	bool isEmpty();
private:
	HeapItem* root;
};

