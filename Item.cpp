#include "Item.h"

// trim from end
static inline std::string& rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string& trim(std::string& s) {
	return rtrim(s);
}

void Item::GetBirdsFile()
{
	string str_path;
	char full[_MAX_PATH];
	if (_fullpath(full, ".\\", _MAX_PATH) != NULL)
		str_path = string(full);
	str_path = str_path + "Birds.txt";

	ifstream binary_file(str_path, ios::binary | ios::in);
	string line;

	if (!binary_file.good()) {
		throw exception("Birds.txt could not be found. Please keep it as instructed");
	}
	if (binary_file.is_open()) {
		while (getline(binary_file, line)) {
			line = trim(line);
			if (line == "") continue;
			this->Birds.push_back(line);
		}
	}
	if (Birds.size() == 0) throw exception("Birds.txt file is empty");
}

int Item::CreateRandomNumber(int i_range, int f_range)
{
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr((unsigned int)i_range, (unsigned int)f_range);
	return distr(eng);
}

string Item::GetName(int index)
{
	try
	{
		if (this->Birds.size() == 0) throw exception("No name found for item");
		else return this->Birds[index];
	}
	catch (const std::exception& err)
	{
		cout << err.what() << endl;
	}
}

Item::Item() {
	if (!this->init) {
		this->GetBirdsFile(); this->init = 1; this->BirdsNumber = Birds.size();
	}
	
	Date i_Date = Date(1, 1, 1950);
	Date f_Date = Date(1, 1, 2020);
	int Group_t = this->CreateRandomNumber(65, 90);
	int Subgroup_t = this->CreateRandomNumber(0, 99);
	int Name_t = this->CreateRandomNumber(1, this->BirdsNumber);

	Date Timestamp_t;
	Timestamp_t = Timestamp_t.CreateRandomDate(i_Date, f_Date);
	
	this->Group = (char)Group_t;
	this->Subgroup = Subgroup_t;
	this->Name = this->GetName(Name_t);
	this->Timestamp = Timestamp_t;
	this->ID = this->Group + to_string(this->Subgroup);
}

Item::Item(char c, int i, string s, Date d)
{
	if (!this->init) {
		this->GetBirdsFile(); this->init = 1; this->BirdsNumber = Birds.size();
	}

	if ((int)c >= 65 || (int)c <= 90) this->Group = c; 
	else throw invalid_argument("Group is invalid");
	if (i >= 0 || i <= 99) this->Subgroup = i;
	else throw invalid_argument("Subgroup is invalid");
	if (s != "") this->Name = s; 
	else throw invalid_argument("Name is invalid");
	this->Timestamp = d;
	this->ID = this->Group + to_string(this->Subgroup);
}

Item::Item(char c)
{
	Item item = Item();
	if ((int)c >= 65 || (int)c <= 90) this->Group = c;
	else throw invalid_argument("Group is invalid");
	this->Subgroup = item.Subgroup;
	this->Name = item.Name;
	this->Timestamp = item.Timestamp;
	this->ID = this->Group + to_string(this->Subgroup);
}

Item::Item(int i)
{
	Item item = Item();
	if (i >= 0 || i <= 99) this->Subgroup = i;
	else throw invalid_argument("Subgroup is invalid");
	this->Group = item.Group;
	this->Name = item.Name;
	this->Timestamp = item.Timestamp;
	this->ID = this->Group + to_string(this->Subgroup);
}

Item::Item(char c, int i)
{
	Item item = Item();
	if ((int)c >= 65 || (int)c <= 90) this->Group = c;
	else throw invalid_argument("Group is invalid");
	if (i >= 0 || i <= 99) this->Subgroup = i;
	else throw invalid_argument("Subgroup is invalid");
	this->Name = item.Name;
	this->Timestamp = item.Timestamp;
	this->ID = this->Group + to_string(this->Subgroup);
}

Item::Item(const Item& item)
{
	this->Group = item.Group;
	this->Subgroup = item.Subgroup;
	this->Name = item.Name;
	this->Timestamp = item.Timestamp;
	this->ID = item.ID;
}

bool Item::operator==(Item& item) const
{
	return this->Name == item.Name;
}

ostream& operator<<(ostream& ostr, const Item& item)
{
	string ItemDate = item.Timestamp.ToString();
	ostr << item.Subgroup << ": " << item.Name << " " << ItemDate << std::endl;
	return ostr;
}

Item::~Item()
{

}

