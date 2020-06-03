#pragma once
#include "Main.h"

class Item
{
private:
	bool init = 0;
	int BirdsNumber=0;
	string ID;
	char Group;
	int Subgroup;
	string Name;
	Date Timestamp;
	vector<string> Birds;
public:
	Item();
	Item(char, int, string, Date);
	Item(char);
	Item(int);
	Item(char, int);
	Item(const Item&);
	~Item();
	char GetGroup() { return this->Group; };
	int GetSubgroup() { return this->Subgroup; };
	string GetName() { return this->Name; };
	string GetID() { return this->ID; }
	Date GetDate() { return this->Timestamp; }
	bool operator==(Item&) const;
	friend ostream& operator<<(ostream&, const Item&);
private:
	void GetBirdsFile();
	int CreateRandomNumber(int, int);
	string GetName(int);
};

