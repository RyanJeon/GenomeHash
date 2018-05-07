#include <iostream>
#include <fstream>
#include <vector>
#include "hash_brown.h"


using namespace std;

int main(){
	string file;

	cin >> file;
	cin >> file; 
	ifstream gen(file.c_str());

	float occ = 0.5;
	int kmer; 

	//will store miss match
	int mm;
	string q; //will store a sequence
	string c; //will store letter in genome

	//will store command
	string command;

	//will store genome info
	string genome;  	

	//load info to genome info string
	while(gen >> c){
		genome += c;
	}
	//temporary vector
	vector<string> temp; //will hold sequence 
	vector<int> temp_loc; //will hold location

	int table_size = 100; //initial table size

	cin >> command;
	if(command == "table_size") {cin >> table_size; cin >> command;}

	//make a hash object
	hashBrown potato(table_size);

	while(true){
		if(command == "occupancy") cin >> occ;
		else if(command == "kmer"){
			//set the number for kmer
			cin >> kmer;

			//counter
			int ctr = 0;

			//iterator for genome
			string::iterator it;
			//will contain temporary string
			string temp_str;

			//goes through the genome info to store in hash table
			for(string::iterator i = genome.begin(); i < genome.end(); i++){
				//clears the temporary string
				temp_str.clear();

				//stores first letter
				it = i;
				for(int i = 0; i < kmer; i++){
					temp_str += *it;
					it++;
				}

				temp.push_back(temp_str); //temporary sequence holder
				temp_loc.push_back(ctr); //temporary location holder

				potato.add(temp_str, ctr); //add it to the hashtable

				ctr++;

				//if the occupancy reachs max level
				if(float(ctr)/float(potato.t_size) >= occ){potato.resize(temp, temp_loc);}

				if(int(genome.size()) - ctr < kmer) break;
			}

		}
		else if(command == "quit") break;
		//extra credit.. using vector
		else if(command == "vquery"){
			cin >> mm; //allowed mismatches
			cin >> q; //query
			cout << "Query: " << q << endl;

			int mis = 0;
			//will hold the primer of sequence
			string primer (q, 0, kmer);

			//help counters
			int ctr = 0;
			int ctr2 = 0;

			string result = primer;	

			/*
				same concept with normal query command, but location and sequence are stored in 2 different vectors
				in same index. This does not use hash table.
			*/

			for(unsigned int i = 0; i < temp.size(); i++){
				if(temp[i] == primer){
					for(int j = temp_loc[i]+kmer-1; j < temp_loc[i]+kmer+int(q.size()-primer.size()); j++){
						if(j != temp_loc[i]+kmer-1) result += genome[j];
						if(q[kmer+ctr-1] != genome[j]) mis++;
						ctr++;
					}
					ctr = 0;

					if(mis <= mm) {cout << temp_loc[i] << " " << mis << " " << result << endl; ctr2++;}
					mis = 0;
					result = primer;					
				}
			}

			if(ctr2 == 0) cout << "No Match" << endl;

		}	
		else if(command == "query"){
			cin >> mm; //allowed mismatches
			cin >> q; //query
			cout << "Query: " << q << endl;	

			//will hold the primer of sequence
			string primer (q, 0, kmer);

			//will hold starting point (index point)
			store* start = potato.table()[potato.Hash(primer)];

			//will report mismatches
			int mis = 0;
			//will hold resulting string
			string result = primer; 

			//will help count
			int ctr = 0;
			int ctr2 = 0; //will count how many sequences were valid.
			while(true){
				//if the you found what you are looking for
				if(start->seq == primer && start->loc+int(q.size()-primer.size()) < int(genome.size()) ){
					for(int i = start->loc+kmer-1; i < start->loc+kmer+int(q.size()-primer.size()); i++){
						if(i != start->loc+kmer-1) result += genome[i];
						if(q[kmer+ctr-1] != genome[i]) mis++;
						ctr++;
					}
					ctr = 0;
					//if mismatches are not too much
					if(mis <= mm) {cout << start->loc << " " << mis << " " << result << endl; ctr2++;}
					mis = 0;
					result = primer;
				}
				if(start->next == NULL) break; //break if end of list in index
				start = start->next;
			}
			//no match
			if(ctr2 == 0) cout << "No Match" << endl;
		}
		cin >> command;	
	}


	return 0;
}