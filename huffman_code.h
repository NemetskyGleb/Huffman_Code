/* Алгоритм
1.записываем частоты в таблицу TAB
2.формируем упордоченный список на основе частот 
3.формируем кодовую таблицу
4.кодируем текст по кодовой таблице
*/
#ifndef HUFFMAN_CODE_
#define HUFFMAN_CODE_
#include <iostream>
#include <cstring>
class Node {
private:
	char* str;
	int freq;
	Node *next, *left, *right;
public:
	Node() {
		str = new char[1]; 
		str[0] = '\0';
		freq = 0;
		next = left = right = nullptr;
	}
	Node(char* s, int fr = 0, Node * N = nullptr, Node* L = nullptr, Node* R = nullptr) : freq(fr), next(N), left(L), right(R) {
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	~Node() {
		delete[] str;
	}
	friend class Code;
};

class Code {
private:
	Node* head;
	int type; // type (0,1) - линейный список : дерево
	bool Find(char ch, char* p); // поиск символа в строке
	//void Copy(Node* q, int k, Node* p); // копирует дерево с корнем q, p - предок нового дерева
										// k(0,1) левый : правый потомок
										// не нужна если нет конструктора копирования и оператора присвоения
public:
	Code() : head(nullptr), type(0) { }
	Code(char* s);
	//Code(const Code& );
	//Code& operator=(const Code& );
	void AddToTail(char* s, int fr);
	void AddToTail(Node* p); // при формирование дерева
	void AddToHead(char* s, int fr);
	void AddToHead(Node* p);
	void AddAfter(char* s, int fr, Node* pr);
	void AddAfter(Node* p, Node* pr); 
	void DelHead();
	//void Clear(Node* p);
	//bool Empty();
	
	void PrintList(); // вспомогательная ф-ция
//	void PrintTree(int k, Node* p);
	Node* GetHead() { return head; }

	void FormTree(); // преобразование списка в дерево
	void CodeText(char* s, char* code);
	void DecodeText(char* code, char* dcode);
	void DelTree(Node* tree);
	~Code();
};

#endif