#pragma once
#include "Item.h"

bool SortItemByName(Item*, Item*);
bool SortItemByDate(Item*, Item*);
bool CompareItem(Item*, Item*);
bool IsSameList(list<Item*>, initializer_list<Item*>);

class Data
{
private:
	map<string, list<Item*>> AllItems;
	map<char, map<int, list<Item*>*>*> DataStructure;

public:
	Data(int);
	Data();
	~Data();
	void PrintAll();
	int CountItems();
	map<int, list<Item*>*>* GetGroup(char);
	void PrintGroup(char);
	int CountGroupItems(char);
	list<Item*>* GetSubgroup(char, int);
	void PrintSubgroupByNames(char, int);
	void PrintSubgroupByDates(char, int);
	int CountSubgroupItems(char, int);
	Item* GetItem(char, int, string);
	void PrintItem(char, int, string);
	Item* InsertItem(char, int, string, Date);
	list<Item*>* InsertSubgroup(char, int, initializer_list<Item*>);
	map<int, list<Item*>*>* InsertGroup(char, initializer_list<int>, initializer_list<initializer_list<Item*>>);
	bool RemoveItem(char, int, string);
	bool RemoveSubgroup(char, int);
	bool RemoveGroup(char);

};

