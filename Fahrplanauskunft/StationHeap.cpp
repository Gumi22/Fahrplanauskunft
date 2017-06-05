#include "stdafx.h"
#include "StationHeap.h"


StationHeap::StationHeap()
{
	Count = 0;
}


StationHeap::~StationHeap()
{
	HeapItem* temp;
	while (root != nullptr) {
		temp = root;
		root = root->next;
		delete temp;
	}
}

void StationHeap::insertStationSorted(Station* newStation, int weightedValue, Station* previous, std::string line) {
	Count++;
	if (root != nullptr) { //wenn schon etwas eingef�gt wurde
		HeapItem* temp = root;
		while (temp->next != nullptr && weightedValue > temp->next->weightedValue) { //solange weitersuchen bis der n�chste Wert <= meinem neuen Wert ist oder nicht vorhanden ist
			temp = temp->next;
		}
		if (temp->next == nullptr) //wenn am Ende der Liste angelangt ist:
		{
			temp->next = new HeapItem; //Erzeuge ein Neues und h�nge es hinten dran
			temp->next->Item = newStation;
			temp->next->weightedValue = weightedValue;
			temp->next->predecessor = previous;
			temp->next->line = line;
			temp->next->next = nullptr;
		}
		else {
			HeapItem* temp2 = temp->next; //Link auf gr��eren wert zwischenspeichern
			temp->next = new HeapItem; //neues einf�gen
			temp->next->Item = newStation;
			temp->next->weightedValue = weightedValue;
			temp->next->predecessor = previous;
			temp->next->line = line;
			temp->next->next = temp2; //zwischengespeicherten Wert dranh�ngen
		}
	}
	else { //Keines war drin, f�ge es hinten dran
		root = new HeapItem;
		root->Item = newStation;
		root->weightedValue = weightedValue;
		root->predecessor = previous;
		root->line = line;
		root->next = nullptr;
	}
}

HeapItem* StationHeap::getNextStation() {
	if (root == nullptr) {
		return nullptr;
	}
	Count--;
	HeapItem* temp = root;
	root = root->next;
	return temp;
}

bool StationHeap::isEmpty() {
	if (root == nullptr) {
		return true;
	}
	return false;
}

int StationHeap::getCount() {
	return Count;
}