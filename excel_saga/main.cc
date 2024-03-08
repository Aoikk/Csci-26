#include "/public/read.h"
#include <vector>
#include <algorithm>
using namespace std;

void die() {
	cout << "BAD INPUT!" << endl;
	exit(1);
}
string convert_int(int temp){
	string combo;

	while (temp > 0) {
	char letter =  'Z';
	int temp2 = 26 - (temp % 26);
	if (temp2 == 26) temp2 = 0;
	letter -= temp2;
	combo.push_back(letter);
	if (temp2 == 0) temp -= 1;
	temp = temp/26;
	}
	reverse(combo.begin(),combo.end());
	return combo;
}
int convert_label(string temp){
	int columnInt = 0;
	//
	for (auto c : temp) {
		columnInt = columnInt * 26 + (c - 'A' + 1);
	}
	//
	return columnInt;
}


int main() {
	int choice = 0;
	cout << "1. Convert integer to Excel column label\n";
	cout << "2. Convert Excel column label to integer\n";

	cin >> choice;
	if (!cin) die();
	if (choice > 2 or choice < 1) die();
	if (choice == 1) {
	int userInt = 0;
	cout << "Please enter an integer:" << endl;
	cin >> userInt;
	if (!cin) die();
	cout << convert_int(userInt) << endl;
	}
	if (choice == 2) {
	string userColumn;
	userColumn = readline("Please enter a column label:\n");
	bool alpha = true;
	for (char c : userColumn) {
		if (!isalpha(c)) alpha = false;
		}
	if (alpha == false) die();
	cout << convert_label(userColumn) << endl;
	}
}
