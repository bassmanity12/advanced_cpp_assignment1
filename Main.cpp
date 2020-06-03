#include "Main.h"
#include "Data.h"
#include "Item.h"

void CheckInputError()
{
	if (cin.fail())
	{
		cout << "Failure getting input \n";
		cin.clear();
	}
}

void start() 
{
	Data* ds = new Data;
	int command = 0, sec_command = 0, ter_command = 0;

    cout << "\n(1) Create Data Structure" << endl;
    cout << "(2) Print Data Structure" << endl;
    cout << "(3) Print an Item" << endl;
    cout << "(4) Print a Group" << endl;
    cout << "(5) Print a Subgroup (By Names)" << endl;
    cout << "(6) Print a Subgroup (By Dates)" << endl;
    cout << "(7) Count Items" << endl;
    cout << "(8) Count Items in a Group" << endl;
    cout << "(9) Count Items in a Subgroup" << endl;
    cout << "(10) Insert an Item" << endl;
    cout << "(11) Insert a Group" << endl;
    cout << "(12) Insert a Subgroup" << endl;
    cout << "(13) Remove an Item" << endl;
    cout << "(14) Remove a Group" << endl;
    cout << "(15) Remove a Subgroup" << endl;
    cout << "(16) Exit" << endl;

    command = 0;
    cout << "Enter task number: ";
    cin >> command;
    CheckInputError();

    cout << "Firstly, creating a data structure" << endl;
    int ItemNumber;
    cout << "Enter item number: ";
    cin >> ItemNumber;
    CheckInputError();

    try
    {
        ds = new Data(ItemNumber);
        cout << "Data structure is created with " << ItemNumber << " items" << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
        cout << "Failure creating data structure" << endl;
    }

    // printing data structure
    try
    {
        cout << "Printing data stucture\n" << endl;
        ds->PrintAll();
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
        cout << "Failure with printing" << endl;

    }
    cout << "Counting Items" << endl;
    int count = 0;
    try
    {
        count = ds->CountItems();
        cout << count << " item(s) in data stucture" << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }


    list<int> SubgroupTasks = { 5,6,9,12,15,18,3,10,13,16 };
    list<int> ItemTasks = { 3,10,13,16 };
    list<int>::iterator iterSubgroup = find(SubgroupTasks.begin(), SubgroupTasks.end(), command);
    list<int>::iterator iterItem = find(ItemTasks.begin(), ItemTasks.end(), command);

    char iGroup; int iSubgroup; string ItemName;
    cout << "Enter group(A-Z): "; cin >> iGroup;
    CheckInputError();

    if (iterSubgroup != SubgroupTasks.end()) {
        cout << "Enter subgroup(0-99): "; cin >> iSubgroup;
        CheckInputError();

        if (iterItem != ItemTasks.end()) {
            cout << "Enter item name: ";
            std::getline(std::cin >> std::ws, ItemName);
            CheckInputError();
        }
    }

    try
    {
        cout << "Printing group " << iGroup << "\n" << endl;
        ds->PrintGroup(iGroup);
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
        cout << "Failure with printing" << endl;
    }

    cout << "Counting items in a group" << endl;
    int count = 0;
    try
    {
        count = ds->CountGroupItems(iGroup);
        if (count == 0) throw exception("No item found");
        cout << count << " item(s) in group " << iGroup << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }

    try
    {
        cout << "Inserting groups, for 17, 25, 33 and 49" << endl;
        Item* item1 = new Item(iGroup, 17);
        Item* item2 = new Item(iGroup, 17);
        Item* item3 = new Item(iGroup, 25);
        Item* item4 = new Item(iGroup, 25);
        Item* item5 = new Item(iGroup, 25);
        Item* item6 = new Item(iGroup, 33);
        Item* item7 = new Item(iGroup, 33);
        Item* item8 = new Item(iGroup, 49);

        initializer_list<int> subgroups = { 17,25,33,49 };
        initializer_list<initializer_list<Item*>> items = {
            {item1, item2}, {item3, item4, item5}, {item6, item7}, {item8}
        };
        if (ds->InsertGroup(iGroup, subgroups, items) != nullptr)
            cout << "Successfully inserted a group(" << iGroup << ") with 8 random items" << endl;
        else throw exception("Failure with inserting group");
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }
    cout << "Removing groups" << endl;
    bool success = 0;
    try
    {
        success = ds->RemoveGroup(iGroup);
        if (!success) throw invalid_argument("Group does not exist");
        cout << "Successfully removed group " << iGroup << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }
    cout << "Printing subgroup by name" << endl;
    try
    {
        cout << "Printing subgroup " << iSubgroup << " of group " << iGroup << "\n" << endl;
        ds->PrintSubgroupByNames(iGroup, iSubgroup);
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
        cout << "Failure with printing" << endl;
    }
    cout << "Printing subgroup by date" << endl;
    try
    {
        cout << "Printing subgroup " << iSubgroup << " of group " << iGroup << "\n" << endl;
        ds->PrintSubgroupByDates(iGroup, iSubgroup);
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
        cout << "Failure with printing" << endl;
    }

    cout << "Counting items in subgroup" << endl;
    int count = 0;
    try
    {
        count = ds->CountSubgroupItems(iGroup, iSubgroup);
        if (count == 0) throw exception("No item fround");
        cout << count << " item(s) in subgroup " << iSubgroup << " of group " << iGroup << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }
    cout << "Inserting a subgroup" << endl;
    try
    {
        Item* item1 = new Item(iGroup, iSubgroup);
        Item* item2 = new Item(iGroup, iSubgroup);
        Item* item3 = new Item(iGroup, iSubgroup);
        Item* item4 = new Item(iGroup, iSubgroup);
        Item* item5 = new Item(iGroup, iSubgroup);
        Item* item6 = new Item(iGroup, iSubgroup);
        Item* item7 = new Item(iGroup, iSubgroup);
        initializer_list<Item*> items = {
            item1, item2, item3, item4, item5, item6, item7
        };
        if (ds->InsertSubgroup(iGroup, iSubgroup, items) != nullptr)
            cout << "Successfully inserted a subgroup(" << iSubgroup << ") in group(" << iGroup
            << ") with 7 random items" << endl;
        else throw exception("Failure with inserting subgroup");
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }

    cout << "Removing the subgroup" << endl;
    bool success = 0;
    try
    {
        success = ds->RemoveSubgroup(iGroup, iSubgroup);
        if (!success) throw invalid_argument("Subgroup does not exist");
        cout << "Successfully removed subgroup " << iSubgroup << " of group " << iGroup << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }
    cout << "Printing an iteem" << endl;
    try
    {
        ds->PrintItem(iGroup, iSubgroup, ItemName);
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }
    cout << "Inserting an item" << endl;
    Date dd = Date();
    Item* successI = ds->InsertItem(iGroup, iSubgroup, ItemName, dd);
    if (successI == nullptr) cout << "Failure inserting item" << endl;
    else cout << "Succssfully inserted item: " << successI << endl;

    cout << "Removing the item" << endl;
    bool success = 0;
    try
    {
        success = ds->RemoveItem(iGroup, iSubgroup, ItemName);
        if (!success) throw invalid_argument("Item does not exist");
        cout << "Successfully removed item " << ItemName << " from subgroup " << iSubgroup
            << " of group " << iGroup << endl;
    }
    catch (const std::exception & err)
    {
        cout << err.what() << endl;
    }
        
    cout << "Destroying the class, cleaning up and exiting" << endl;
    ds->~Data();
}
