#include <iostream>
#include "LL.h"

using namespace std;

int main(){
	cout << "Add something below. " << endl;

	int add = 0;
	int baliktadAdd = 0;

	LL<int>* pawala = new LL<int>();

	while (cin >> add) {
		pawala->insertHead(add);
		if (add == -1) break;
	}
	pawala->print();

	cout << "\n\nWhat should we remove?" << endl;
	
	cin >> baliktadAdd;
	
	pawala->remove(baliktadAdd);
	pawala->print();

	pawala->clear();

	system("pause");
	return 0;
}