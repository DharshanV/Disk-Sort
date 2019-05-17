#ifndef DISK_SORT_H
#define DISK_SORT_H
#include <iostream>
#include <fstream>
#include <string>
#include "sort_function.h"
#include "Heap.h"
using namespace std;

struct Data
{
	int data;
	int index;
	Data() {
		data = 0;
		index = 0;
	}
	Data(int data, int index) {
		this->data = data;
		this->index = index;
	}
	bool operator <(const Data& rhs) const
	{
		return this->data < rhs.data;
	}
	bool operator >(const Data& rhs) const
	{
		return this->data > rhs.data;
	}
	bool operator == (const Data& rhs) const
	{
		return this->data == rhs.data;
	}
};

class DiskSort {
public:
	DiskSort(string fileName, int T);
	~DiskSort();
	void sort();
private:
	void write_chunk(int chunkId, int* ptr, int n);
	void write_output(int outputId, int* data, int n);
	int* load_to_Memory(int chunkId,int& n);
	void make_chunks(int S, int T);
	void sort_chunks();
	void merge_chunks();
	void final_merge();
private:
	string* chunkFileNames;
	string fileName;
	int chunkCount;
	int chunkSize;
};

DiskSort::DiskSort(string fileName,int T) {
	chunkCount = 0;
	chunkSize = T;
	chunkFileNames = NULL;
	this->fileName = fileName;
}

DiskSort::~DiskSort()
{
	for (int i = 0; i < chunkCount; i++) {
		remove(chunkFileNames[i].c_str());
	}
	delete[] chunkFileNames;
}

void DiskSort::make_chunks(int S, int T) {
	chunkCount = int(ceil(double(S) / T));
	chunkFileNames = new string[chunkCount];
	ifstream in(fileName);
	for (int i = 0; i < chunkCount; i++) {
		string name = "chunk" + to_string(i) + ".txt";
		chunkFileNames[i] = name;
		ofstream out;
		out.open(name);
		string read;
		string fileOut;
		fileOut.reserve(T);
		for (int j = 0; j < T; j++) {
			getline(in, read);
			fileOut += read;
			fileOut += "\n";
			if (in.eof()) break;
		}
		out << fileOut << endl;
		out.close();
		cout << "Chunk" + to_string(i) << " created" << endl;
	}
	in.close();
}

void DiskSort::sort_chunks()
{
	for (int i = 0; i < chunkCount; i++) {
		cout << "Sorting chunk" << i << endl;
		int n = 0;
		int* ptr = load_to_Memory(i,n);
		merge_sort(ptr, n);
		write_chunk(i, ptr, n);
		delete[] ptr;
	}
}

void DiskSort::merge_chunks()
{
	cout << "Merging chunks" << endl;
	ifstream* runReader = new ifstream[chunkCount];
	int* outputBuffer = new int[chunkSize];
	int index = 0;
	int exhaustedCount = 0;
	bool finished = false;
	bool firstRun = true;
	for (int i = 0; i < chunkCount; i++) {
		runReader[i].open("chunk" + to_string(i) + ".txt");
	}

	Heap<Data> heap;
	string read;
	int outputIndex = 0;
	while (!finished) {
		finished = (exhaustedCount == chunkCount);
		if (finished && outputIndex <= chunkCount) {
			break;
		}
		if (firstRun) {
			for (int i = 0; i < chunkCount; i++) {
				getline(runReader[i], read);
				heap.insert(Data(atoi(read.c_str()),i));
			}
			firstRun = false;
		}
		
		Data temp = heap.pop();
		outputBuffer[index] = temp.data;
		if (runReader[temp.index].peek() != '\n') {
			getline(runReader[temp.index], read);
			heap.insert(Data(atoi(read.c_str()), temp.index));
		}
		else {
			runReader[temp.index].close();
			remove(string("chunk" + to_string(temp.index) + ".txt").c_str());
			exhaustedCount++;
		}
		index++;
		if (index >= chunkSize) {
			write_output(outputIndex, outputBuffer, index);
			index = 0;
			outputIndex++;
		}
	}
	delete[] outputBuffer;
	delete[] runReader;
}

void DiskSort::final_merge()
{
	ofstream out;
	string line;
	out.open("sorted data.txt");
	for (int i = 0; i < chunkCount; i++) {
		ifstream reader;
		string fileName("output" + to_string(i) + ".txt");
		reader.open(fileName);
		string fileOut;
		fileOut.reserve(chunkSize);
		while (reader.good()) {
			getline(reader, line);
			if (reader.eof())break;
			fileOut += line;
			fileOut += "\n";
		}
		out << fileOut;
		fileOut.clear();
		reader.close();
		remove(fileName.c_str());
	}
	out.close();
}

void DiskSort::write_chunk(int chunkId, int* ptr, int n)
{
	ofstream out;
	out.open(chunkFileNames[chunkId].c_str());
	string fileOut;
	fileOut.reserve(n);
	
	for (int i = 0; i < n; i++) {
		fileOut += to_string(ptr[i]);
		fileOut += "\n";
	}
	out << fileOut << endl;
	out.close();
}

void DiskSort::write_output(int outputId, int* data, int n)
{
	ofstream out;
	out.open("output" + to_string(outputId) + ".txt");
	string fileOut;
	fileOut.reserve(n);

	for (int i = 0; i < n; i++) {
		fileOut += to_string(data[i]);
		fileOut += "\n";
	}
	out << fileOut << endl;
	out.close();
}

int* DiskSort::load_to_Memory(int chunkId,int& n)
{
	int* ptr = new int[chunkSize];
	ifstream in(chunkFileNames[chunkId]);
	int index = 0;
	while (in >> ptr[index]) {
		index++;
	}
	n = index;
	return ptr;
}

void DiskSort::sort() {
	int S = atoi(fileName.substr(fileName.find_first_of(' ')).c_str());
	make_chunks(S, chunkSize);
	sort_chunks();
	merge_chunks();
	final_merge();
}
#endif // !DISK_SORT_H
