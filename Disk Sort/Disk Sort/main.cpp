#include <iostream>
#include "DiskSort.h"
#include "random.h"
#include "timer.h"
using namespace std;

string makedata() {
	int S = 1000000;
	Random<int> r;
	ofstream out;
	string fileName = "data " + to_string(S) + ".txt";
	out.open(fileName);
	for (int i = S; i >=1; i--) {
		out << i;
		//out << r.next(1, 99999);
		if (i != 1)out << endl;
	}
	out.close();
	return fileName;
}

int main() {
	timer t;
	t.start();
	cout << "Making file" << endl;
	string fileName = makedata();
	DiskSort disksort(fileName,100000);
	disksort.sort();
	cout << "Finished" << endl;
	t.stop();
	cout << "Elapsed : " << t.duration() << endl;
	return 0;
}