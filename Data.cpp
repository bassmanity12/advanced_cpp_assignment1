#include "Main.h"
#include "Data.h"

bool SortItemByName(Item* item1, Item* item2)
{
	return item1->GetName() < item2->GetName();
}

bool SortItemByDate(Item* item1, Item* item2)
{
	return item1->GetDate() < item2->GetDate();
}

bool CompareItem(Item* item1, Item* item2)
{
	return (item1->GetName() == item2->GetName());
}

bool IsSameList(list<Item*> l_list, initializer_list<Item*> ref_list)
{
	if (l_list.size() != ref_list.size()) return 0;

	return ::equal(l_list.begin(), l_list.end(), ref_list.begin(), CompareItem);

}


Data::Data(int i)
{
	for (int j = 0; j < i; j++) {
		Item* item_t = new Item();
		this->AllItems[item_t->GetID()].push_back(item_t);
	}
	for (auto x : this->AllItems) {
		x.second.sort(SortItemByName);
	}
	int iSubgroupNumber = this->AllItems.size();
	vector<map<int, list<Item*>*>*> SubItems(iSubgroupNumber);
	int it = -1;
	map<string, list<Item*>>::iterator iter = this->AllItems.begin();
	int init = 0;
	char cGroup, pGroup;
	for (auto x : this->AllItems) {
		bool IsSameGroup = 0;
		cGroup = x.second.back()->GetGroup();
		//cout << "cGroup: " << cGroup << " ";
		int cSubgroup = x.second.back()->GetSubgroup();
		//cout << "cSubgroup: " << cSubgroup << " ";
		//if (it == -1)cout << "Same Group: " << IsSameGroup << endl;
		if (it > -1) {
			if (cGroup == pGroup) IsSameGroup = 1;
			else IsSameGroup = 0;
			//cout << "Same Group: " << IsSameGroup << endl;
		}
		if (IsSameGroup) {
			it--;
			list<Item*>* pListItem = &iter->second;
			SubItems[it + 1]->insert(make_pair(cSubgroup, pListItem));
			//cout << "ID from SubItems: " << SubItems[it + 1]->at(cSubgroup)->front()->GetID() << endl;
		}
		else {
			list<Item*>* pListItem = &iter->second;
			map<int, list<Item*>*>* pMapItem = new map<int, list<Item*>*>();
			pMapItem->insert(make_pair(cSubgroup, pListItem));
			SubItems[it + 1] = pMapItem;
			//cout << "ID from SubItems: " << SubItems[it+1]->at(cSubgroup)->front()->GetID() << endl;
			if (init) {
				//cout << "Saving subitems into datastucture" << endl;
				map<int, list<Item*>*>* t_map_insert = SubItems[it];
				this->DataStructure.insert(make_pair(pGroup, t_map_insert));
				//cout << "ID from this->DataStructure: " << (this->DataStructure[pGroup]->end())->second->front()->GetID() << endl;
			}
		}
		iter++;
		if (iter == this->AllItems.end()) {
			//cout << "end" << endl;
			map<int, list<Item*>*>* t_map_insert = SubItems[it + 1];
			this->DataStructure[cGroup] = t_map_insert;
			//cout << "ID from this->DataStructure: " << (this->DataStructure[cGroup]->begin())->second->front()->GetID() << endl;
		}
		pGroup = cGroup;
		init = 1;
		it++;

	}
}

Data::Data()
{
	this->DataStructure.clear();
}

Data::~Data()
{
	if (!this->DataStructure.empty()) {
		for (auto x : this->DataStructure) {
			for (auto y : *x.second) {
				for (auto z : *y.second) {
					delete z;
				}
				//delete y.second;
				y.second->clear();
			}
			delete x.second;
		}
		this->DataStructure.clear();
	}
}

void Data::PrintAll()
{

	if (this->DataStructure.empty()) throw exception("Data structure is empty");
	for (auto x : this->DataStructure) {
		cout << x.first << ":" << endl;
		for (auto y : *x.second) {
			y.second->sort(SortItemByName);
			for (auto z : *y.second) {
				cout << *z << endl;
			}
		}
		cout << endl;
	}

}

int Data::CountItems()
{
	int count = 0;
	if (this->DataStructure.empty()) throw exception("Data structure is empty");
	for (auto x : this->DataStructure) {
		for (auto y : *x.second) {
			for (auto z : *y.second) {
				count++;
			}
		}
	}
	return count;
}

void Data::PrintGroup(char c)
{
	map<int, list<Item*>*>* pGroup = GetGroup(c);
	//string errMessage = "No items with Group: " + c + string(" is found");
	//const char* cerrMessage = errMessage.c_str();
	if (pGroup == nullptr) throw invalid_argument("No item found");
	else {
		cout << c << ":" << endl;
		for (auto x : *pGroup) {
			x.second->sort(SortItemByName);
			for (auto y : *x.second) {
				cout << *y << endl;
			}
		}
	}
}

int Data::CountGroupItems(char c)
{
	int count = 0;
	if (this->DataStructure.empty()) throw exception("Data structure is empty");
	map<int, list<Item*>*>* pGroup = GetGroup(c);
	if (pGroup == nullptr) return 0;
	for (auto x : *pGroup) {
		for (auto y : *x.second) {
			count++;
		}
	}
	return count;
}

void Data::PrintSubgroupByNames(char c, int i)
{

	list<Item*>* pSubgroup = GetSubgroup(c, i);
	//string errMessage = "No items with Group: " + c + string(" and Subgroup: ") + to_string(i) + string(" is found");
	//const char* cerrMessage = errMessage.c_str();
	if (pSubgroup == nullptr) throw invalid_argument("No Item");
	else {
		pSubgroup->sort(SortItemByName);
		for (auto x : *pSubgroup) {
			cout << *x << endl;
		}
	}

}

void Data::PrintSubgroupByDates(char c, int i)
{

	list<Item*>* pSubgroup = GetSubgroup(c, i);
	//string errMessage = "No items with Group: " + c + string(" and Subgroup: ") + to_string(i) + string(" is found");
	//const char* cerrMessage = errMessage.c_str();
	if (pSubgroup == nullptr) throw invalid_argument("No Item");
	else {
		pSubgroup->sort(SortItemByDate);
		for (auto x : *pSubgroup) {
			cout << *x << endl;
		}
	}

}

int Data::CountSubgroupItems(char c, int i)
{
	int count = 0;
	list<Item*>* pSubgroup = GetSubgroup(c, i);
	if (pSubgroup == nullptr) return 0;
	for (auto x : *pSubgroup) {
		count++;
	}
	return count;
}


Item* Data::GetItem(char c, int i, string s)
{
	list<Item*>* pSubgroup = GetSubgroup(c, i);
	if (pSubgroup == nullptr) return nullptr;
	for (auto x : *pSubgroup) {
		if (s == x->GetName()) return x;
	}
	return nullptr;
}

void Data::PrintItem(char c, int i, string s)
{

	Item* pItem = GetItem(c, i, s);
	if (pItem == nullptr)throw invalid_argument("No item found");
	cout << endl;
	cout << *pItem << endl;

}

Item* Data::InsertItem(char c, int i, string s, Date d)
{
	try
	{
		// Searching item 
		Item* pItem = GetItem(c, i, s);
		if (pItem != nullptr) throw invalid_argument("Item already exists");
		// Creating new item
		Item* pNewItem = new Item(c, i, s, d);
		// Searching subgroup and inserting
		list<Item*>* pSubgroup = GetSubgroup(c, i);
		if (pSubgroup != nullptr) { pSubgroup->push_back(pNewItem); return pNewItem; }
		// Creating new subgroup
		list<Item*>* pNewSubgroup = new list<Item*>({ pNewItem });
		// Searching group
		map<int, list<Item*>*>* pGroup = GetGroup(c);
		if (pGroup != nullptr) { pGroup->insert(make_pair(i, pNewSubgroup)); return pNewItem; }
		// Creating group
		map<int, list<Item*>*>* pNewGroup = new map<int, list<Item*>*>();
		pNewGroup->insert(make_pair(i, pNewSubgroup));
		this->DataStructure.insert(make_pair(c, pNewGroup));
		return pNewItem;
	}
	catch (const std::exception & err)
	{
		cout << err.what() << endl;
		return nullptr;
	}
}

list<Item*>* Data::GetSubgroup(char c, int i)
{
	map<int, list<Item*>*>* pGroup = GetGroup(c);
	if (pGroup == nullptr) return nullptr;
	if (pGroup->find(i) == pGroup->end()) return nullptr;
	return pGroup->at(i);
}

map<int, list<Item*>*>* Data::GetGroup(char c)
{
	if (this->DataStructure.find(c) == this->DataStructure.end()) return nullptr;
	return this->DataStructure[c];
}

list<Item*>* Data::InsertSubgroup(char c, int i, initializer_list<Item*> items)
{
	try
	{
		// Searching subgroup
		list<Item*>* pSubgroup = GetSubgroup(c, i);
		// if Subgroup found
		if (pSubgroup != nullptr) {
			// if same items exist in subgroup. exit with exception
			if (IsSameList(*pSubgroup, items)) throw exception("Subgroup already exists");
			// delete items to insert new items
			else {
				for (auto x : *pSubgroup) delete x;
				pSubgroup->clear();
			}
		}
		// if Subgroup not found create a new list
		else pSubgroup = new list<Item*>();
		// Inserting items to list
		for (auto x : items) pSubgroup->push_back(x);
		// Searching group
		map<int, list<Item*>*>* pGroup = GetGroup(c);
		if (pGroup != nullptr) { pGroup->insert(make_pair(i, pSubgroup)); return pSubgroup; }
		// Creating group
		map<int, list<Item*>*>* pNewGroup = new map<int, list<Item*>*>();
		pNewGroup->insert(make_pair(i, pSubgroup));
		this->DataStructure.insert(make_pair(c, pNewGroup));
		return pSubgroup;
	}
	catch (const std::exception & err)
	{
		cout << err.what() << endl;
		return nullptr;
	}
}

map<int, list<Item*>*>* Data::InsertGroup(char c, initializer_list<int> subgroups, initializer_list<initializer_list<Item*>> items)
{
	try
	{
		map<int, list<Item*>*>* pGroupS = GetGroup(c);
		if (pGroupS != nullptr) throw exception("Group already exists");
		// Creating group
		map<int, list<Item*>*>* pGroup = new map<int, list<Item*>*>();
		initializer_list<initializer_list<Item*>>::iterator iter= items.begin();
		for (auto x : subgroups) {
			list<Item*>* pSubgroup = new list<Item*>();
			for (auto y : *iter) {
				pSubgroup->push_back(y);
			}
			pGroup->insert(make_pair(x, pSubgroup));
			iter++;
		}
		this->DataStructure.insert(make_pair(c, pGroup));

	}
	catch (const std::exception & err)
	{
		cout << err.what() << endl;
		return nullptr;
	}
}

bool Data::RemoveGroup(char c)
{
	map<int, list<Item*>*>* pGroup = GetGroup(c);
	if (pGroup == nullptr) return 0;
	for (auto x : *pGroup) {
		for (auto y : *x.second) {
			delete y;
		}
	}
	delete pGroup;
	this->DataStructure.erase(c);
	return 1;
}

bool Data::RemoveSubgroup(char c, int i)
{
	map<int, list<Item*>*>* pGroup = GetGroup(c);
	list<Item*>* pSubgroup = GetSubgroup(c, i);
	if (pSubgroup == nullptr) return 0;
	for (auto x : *pSubgroup) {
		delete x;
	}
	pGroup->erase(i);
	return 1;
}

bool Data::RemoveItem(char c, int i, string s)
{
	map<int, list<Item*>*>* pGroup = GetGroup(c);
	list<Item*>* pSubgroup = GetSubgroup(c, i);
	Item* pItem = GetItem(c, i, s);
	if (pItem == nullptr) return 0;
	list<Item*>::iterator iter = find(pSubgroup->begin(), pSubgroup->end(), pItem);
	delete pItem;
	pSubgroup->erase(iter);
	return 1;
}

