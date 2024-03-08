#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

void die() {
	cout << "BAD INPUT!\n";
	exit(1);
}

//O(N)... eh. Could be logN but whatever
//C++20 up in here, compile with -fconcepts
auto is_in(const auto &needle, const auto &haystack) {
	return find(haystack.begin(),haystack.end(),needle) != haystack.end();
}

size_t get_index_of(const string &name, const auto &vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (name == vec.at(i)) return i;
	}
	throw("Aieee, why sempai!?\n");
}

void print_graph(const auto &names, const auto &friends) {
	for (size_t i = 0; i < names.size(); i++) {
		cout << names.at(i) << ": ";
		for (size_t x : friends.at(i)) {
			cout << names.at(x) << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<string> names; //Holds all the usernames
	vector<vector<size_t>> friends; //Holds who is friends, by index
	while (true) {
		cout << "Enter a username to add (QUIT to quit):\n";
		string new_name;
		cin >> new_name;
		if (!cin) die();
		if (new_name == "QUIT") break;
		if (is_in(new_name,names)) {
			cout << "That name is already in the system, soz.\n";
			continue;
		}
		names.push_back(new_name);
		vector<size_t> empty_list;
		friends.push_back(empty_list);
	}
	while (true) {
		cout << "Give two usernames to make friends (QUIT to quit).\n";
		string name1, name2;
		cin >> name1;
		if (!cin) die();
		if (name1 == "QUIT") break;
		cin >> name2;
		if (!cin) die();
		if (name2 == "QUIT") break;
		if (!is_in(name1,names)) {
			cout << "Sorry, " << name1 << " don't exist none.\n";
			continue;
		}
		if (!is_in(name2,names)) {
			cout << name2 << " doesn't exist, why are you trying to friend a ghost?\n";
			continue;
		}
		size_t index_of_name1 = get_index_of(name1,names);
		size_t index_of_name2 = get_index_of(name2,names);
		auto& name1_friends = friends.at(index_of_name1);
		auto& name2_friends = friends.at(index_of_name2);
		if (is_in(index_of_name2,name1_friends)) {
			cout << "They are already friends, you can't be double friends, sorry.\n";
			continue;
		}
		name1_friends.push_back(index_of_name2); //Name2 is now friends with name1
		name2_friends.push_back(index_of_name1); //Name1 is now friends with name2
	}
	assert(names.size() == friends.size());
	print_graph(names,friends);
	while (true) {
		cout << "Whose complete network do you want to print? (QUIT to quit)\n";
		string name;
		cin >> name;
		if (name == "QUIT") break;
		if (!cin) die();
		if (!is_in(name,names)) {
			cout << "Sorry they don't exist, try again!\n";
			continue;
		}
		cout << "IMMEDIATE FRIENDS:\n";
		size_t index = get_index_of(name,names);
		cout << names.at(index) << ": ";
		for (size_t x : friends.at(index)) {
			cout << names.at(x) << " ";
		}
		cout << endl;
		vector<size_t> processed;
		vector<size_t> to_process = friends.at(index);
		while(to_process.size()) {
			size_t cur = to_process.back(); //In reality, front is more common
			to_process.pop_back();
			if (is_in(cur,processed)) continue;
			processed.push_back(cur);
			for (size_t x : friends.at(cur)) {
				if (is_in(x,processed)) continue;
				to_process.push_back(x);
			}
		}
		cout << "FULL NETWORK:\n";
		cout << names.at(index) << ": ";
		for (size_t x : processed) {
			cout << names.at(x) << " ";
		}
	}
}












