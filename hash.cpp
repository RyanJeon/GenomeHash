#include <iostream>
#include <cstdlib>
#include "hash_brown.h"

using namespace std;


int hashBrown::Hash(string key){
	int hash = 0;
	int index; 

	//adding up each letters value!
	for(unsigned int i = 0; i < key.length(); i++){
		hash += (int)key[i];
	}

	index = hash % t_size;

	return index;
}

hashBrown::~hashBrown(){
	destroy();
}



//destroys
void hashBrown::destroy(){
	//will store pointers to delete
	vector<store*> ptrs;
	for(int i = 0; i < t_size; i++){
		store* p = hashT[i];
		//goes through all the elements in index
		while(p->next != NULL){
			ptrs.push_back(p);
			p = p->next;
		}
		ptrs.push_back(p);
	}

	//destroying starts
	for(unsigned int i = 0; i < ptrs.size(); i++){
		store* p = ptrs[i];
		delete p;
	}
}

void hashBrown::add(string seq, int loc){

	int index = Hash(seq); //hash the sequqnce
	//not there
	if(hashT[index]->seq == "vac"){
		hashT[index]->seq = seq;
		hashT[index]->loc = loc;
	}
	//if already something there
	else{
		store* azn = new store;

		azn->seq = seq;
		azn->loc = loc;
		azn->next = NULL;

		//will add the element to the end of the buckit
		store* p = hashT[index];
		while(p->next != NULL){
			p = p->next;
		}
		//now it's last element in the list
		p->next = azn;

	}


}

void hashBrown::resize(const vector<string>& temp, const vector<int>& temp_loc){
	destroy(); //destroy original table
	hashT.clear(); //clear the original table

	t_size = t_size * 2; //double the table size

	//create empty table with new size 
	for(int i = 0; i < t_size; i++){
		store* tim = new store;

		tim->seq = "vac";
		tim->loc = 0;
		tim->next = NULL;

		hashT.push_back(tim);
	}

	//rehashing
	for(unsigned int i = 0; i < temp.size(); i++){
		add(temp[i], temp_loc[i]);
	}
}