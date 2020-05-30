#include <iostream>
#include "../lib/huffman_code.h"

int main() {
	using namespace std;
	char* s = new char[100];
	char* code = new char[200];
	cout << "Enter string: ";
	cin.getline(s, 80);
	Code a(s);
	a.FormTree();
	a.CodeText(s, code);
	cout << "Code: " << code << std::endl;
	char* dcode = new char[100];
	a.DecodeText(code, dcode);
	cout << "Decoded text: " << dcode << std::endl;
	delete[] s;
	delete[] code;
	delete[] dcode;
	return 0;
}