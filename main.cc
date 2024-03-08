#include <iostream>
#include <vector>
#include "/public/read.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void die() {
	cout << "BAD INPUT!" << endl;
	exit(1);
}

int main() {
	int count = 0;
	int moneyEarned = 0;
	vector<int> userNum;
	vector<int> lottoNum;
	int userSeed;
	cout << "Please enter a seed" << endl;
	cin >> userSeed;
	if (!cin) die();
	srand(userSeed);

	cout << " Please enter 6 numbers between 1 through 69." << endl;
	for (int i = 0; i < 6; i++) {
		int temp = 0;
		cin >> temp;
		if(!cin) die();
		if(temp > 69 or temp < 1)die();
		if (find(userNum.begin(),userNum.end(),temp)  != userNum.end()){
		die();	
		}
		userNum.push_back(temp);
	}
	cout << "Your Numbers: ";
	for (auto x : userNum) {
		cout << x << " ";
	}
	cout << endl;

	cout << "NOW GENERATING THE POWERBALL LOTTO NUMBERS" << endl;

	int temp = 0;
	for (int i = 0; i < 6; i++){
		temp = rand() % 69 + 1;
		while (find(lottoNum.begin(),lottoNum.end(),temp)  != lottoNum.end()){
			temp = rand() % 69 + 1;
		}
		lottoNum.push_back(temp);
	}
	cout << "Lotto Results: ";
	for (auto x : lottoNum) {
		cout << x << " ";
	}
	cout << endl;
	//reminder tomorrow finish make lotto by comparing lottonum to userNum to check how many balls are matching output the money they made
	for (auto x : userNum) {
		for (auto y : lottoNum) {
			if (y == x) count++;
		}
	}
	if (count == 0) moneyEarned = 0;
	if (count == 1) moneyEarned = 4;
	if (count == 2) moneyEarned = 7;
	if (count == 3) moneyEarned = 100;
	if (count == 4) moneyEarned = 50000;
	if (count == 5) moneyEarned = 1'000'000;
	if (count == 6) moneyEarned =4'350'000;

	cout << "You got " << count << " hits!" << endl;
	cout << "You earned " << moneyEarned << "$." <<endl;	
	
}
