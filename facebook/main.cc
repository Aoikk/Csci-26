#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

class Person {
	const string username;
	mutable set<string> connections;
	public:
	Person() = delete; //No default constructor
	Person(string new_username) : username(new_username) {}
	string get_username() const {
		return username;
	}
	void add_connection(string other_name) const {
		auto [iter,inserted] = connections.insert(other_name);
		iter = iter; //Disable unused variable warning
		if (inserted) {} //Insert was successful
		else {} //Insert failed
	}
	const set<string> & get_connections() const
	{
		return connections;
	}
	bool is_added(string other_name) const {
		//Alternative way - does the same as the two lines of find below
		//return connections.count(other_name); //Returns 1 or 0
		auto iter = connections.find(other_name);
		return (iter != connections.end());
	}
	bool operator<(const Person &other) const {
		return username < other.username;
	}
	Person &operator=(const Person &other) {//wadahell am i doing
		this->connections = other.connections;
		return *this;
	}
};

void die() {
	cout << "BAD INPUT!\n";
	exit(1);
}

int main() {
	set<Person> all; //The entire social network
	cout << "Do you wish to implement:\n1. Facebook\n2. Twitter\n";
	int choice = 0;
	if (!(cin >> choice) || choice < 1 || choice > 2) die();
	bool facebook = (choice == 1);
	while (true) {
		cout << "Do you wish to:" << endl;
		cout << "1. Add person\n";
		cout << "2. Add " << (facebook ? "friend" : "follower") << endl;
		cout << "3. Print " << (facebook ? "friends" : "followers") << " of one person\n";
		cout << "4. Print entire social network of one person\n";
		cout << "5. Print all people in the social network\n";
		cout << "6. Quit\n";
		cin >> choice;
		if (choice == 6) exit(0);
		if (!cin or choice < 1 or choice > 6) die();

		if (choice == 1) { //Add person
			cout << "Enter name of person to add:\n";
			string name;
			cin >> name;
			
			//YOU: Write the logic here
			if(all.find(name) == all.end()) {
			all.insert(name);	
			//If they are not in the system yet, print:
				cout << name << " added to network.\n";
			}
			//If they were in the system already, print:
			else if (all.find(name) != all.end()) {
				cout << "Error: " << name  << " in network already.\n";
				continue;
			}
			else {
				die();
			}
		}
		else if (choice == 2) { //Add friend/follower
			cout << "Enter name of person who will add a " << (facebook ? "friend" : "follower") << endl; //Yes I know this is backwards from how Twitter works
			string name;
			cin >> name;
			Person temp(name);

			//YOU: Write the logic here

			//Check if they are in the system, if not:
			if(all.find(name) == all.end()) {
			cout << "Error: " << name << " is not in the network.\n";
			continue;
			}
			temp = *all.find(name);//note for me handles deletion??
			all.erase(all.find(name));

			cout << "Enter name of the person to add: " << endl;
			string name2;
			cin >> name2;
			Person temp2(name2);//me added just for checkpoint

			//Check if name2 is in the system, if not
			if(all.find(name2) == all.end()) {
			cout << "Error: " << name2 << " is not in the network.\n";
			all.insert(temp);
			continue;
			}

			if (facebook) { //Add bidirectional relationship 
				//Check for existing relationship, if so print:
			if (temp.is_added(name2)) {	
				cout << "Error: " << name2 << " is added already.\n";
				all.insert(temp);
				continue; 
			}
				temp2 = *all.find(name2);//same as upper? im too dumb
				all.erase(all.find(name2));
				//Add new Facebook friendship
				//YOU: Add them to each other's networks
				temp.add_connection(name2);
				temp2.add_connection(name);
				all.insert(temp);
				all.insert(temp2);
			}
			else { //Twitter - name gains a follower in name2
				//YOU: Same as above, but Twitter is unidirectional
			if (temp.is_added(name2)) {	
				cout << "Error: " << name2 << " is added already.\n";
				all.insert(temp);
				continue; 
				}
				temp.add_connection(name2);
				all.insert(temp);
			}
		}
		else if (choice == 3) { //Print friends/followers one level deep
			//BUG: This should be (facebook ? "friend" : "follower") but w/e
			//cout << "Enter name of the person to print the followers of: " << endl;
			cout << "Enter name of the person to print the " << (facebook ? "friends" : "followers") << " of: "<< endl; //Yes I know this is backwards from how Twitter works 
			string name;
			cin >> name;
			
			//If trying to print the network of someone not in the system:
			if (all.find(name) == all.end()) {
			cout << "Error: " << name << " is not in the network.\n";
			continue;
			}	
			//YOU: Print all the immediate friends of this person
			else {
			//to do list: Go through a persons connections/ Print it out in a list of abc order
			set<string> personConnections = all.find(name)->get_connections();
			for(const string &a : personConnections) {
					cout << a << endl;
				}
			}
		}
		else if (choice == 4) { //Print all network of one person
			//BUG: This should be (facebook ? "friend" : "follower") but w/e
			//cout << "Enter name of the person to print the followers of: " << endl;
			cout << "Enter name of the person to print the " << (facebook ? "friends" : "followers") << " of: "<< endl; //Yes I know this is backwards from how Twitter works 
			string name;
			cin >> name;

			//If trying to print the network of someone not in the system:
			if (all.find(name) == all.end()) {
			cout << "Error: " << name << " is not in the network.\n";
			continue;
			}

			//Graph traversal - store vertexes processed and to be processed
			//Edges will be loaded from all each time based on name
			set<string> processed;
			set<string> to_process;
			//Start with one name in the to_process list...
			to_process.insert(name);
			while (to_process.size() > 0) { 
				auto first = to_process.begin(); //Get first vertex to process
				string s = *first;
				
				//Step 1. Get all edges from all for the current vertex
				processed.insert(s);
				for(const string &a : all.find(s)->get_connections()) {
					if(processed.find(a) == processed.end()) {
						to_process.insert(a);
					}
				}

				//For each outgoing edge...
					//Step 1.1. Check to see if they have been processed
					//Step 1.2. If we haven't seen them before, add to to-do list

				//Step 2. Add the vertex to the processed list
				//Step 3. Remove the vertex from the to_process list
				to_process.erase(first);
			}
			//After we traverse the graph, print all the names in processed
			for (const string &a : processed) {
				cout << a << endl;
			}
		}
		else { //Print everyone in the network
			for (const Person &a : all) {
				cout << a.get_username() << endl;
			}
		}
	}
}
