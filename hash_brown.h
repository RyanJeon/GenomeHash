#include <iostream>
#include <vector>
#include <list>

using namespace std;

class store{
	public:
		string seq;
		int loc;
		store* next;
};

class hashBrown{
private:


	vector<store*> hashT;

public:
	//constructor
	hashBrown(size_t s) : hashT(s){
		t_size = s;

		hashT.clear();

		for(unsigned int i = 0; i < s; i++){
			store* tim = new store;

			tim->seq = "vac";
			tim->loc = 0;
			tim->next = NULL;

			hashT.push_back(tim);
		}
	}
	~hashBrown();

	int t_size; //table size

	int Hash(string); //hash function
	void add(string, int); //add a sequence
	void destroy(); //destroy table
	void resize(const vector<string>&, const vector<int>&); //resize the table double it

	vector<store*> table() {return hashT;} // return hash table

	//table size

};