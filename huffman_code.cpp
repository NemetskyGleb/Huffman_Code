#include "../lib/huffman_code.h"

void Code::AddToHead(char* s, int fr) {
    Node* q = new Node(s, fr);
    q->next = head;
    head = q;
}

void Code::AddToHead(Node* p) {
    Node* q = new Node(p->str, p->freq);
    q->next = head;
    head = q;
} 

void Code::AddToTail(char* s, int fr) {
    Node* q = new Node(s, fr);
    Node* p = head;
    while(p->next)
        p = p->next;
    p->next = q;
}
void Code::AddToTail(Node* p) {
    Node* temp = new Node(p->str, p->freq, nullptr, p->left, p->right);
    Node* q = head;
    while(q->next)
        q = q->next;
    q->next = temp;
}

void Code::PrintList() {
    Node* p;
    for (p = head; p != nullptr; p = p->next) {
        std::cout << p->str << " " << p->freq << "  ";
    }
    std::cout << std::endl;
}
void Code::DelHead() {
    Node* q = new Node;
    q = head->next;
    delete head;
    head = q;
}
void Code::AddAfter(char* s, int fr, Node* pr) {
    Node* q = new Node(s, fr);
    Node* p = head;
    if (pr) {
        while(strcmp(p->str, pr->str)){
            if(p->next)
                p = p->next;
            else {
                std::cout << "Pr is not in list" << std::endl;
                return;
            }
        }
        if (!p->next){
            p->next = q;
        }
        q->next = p->next;
        p->next = q;
    }
}
void Code::AddAfter(Node* p, Node* pr) {
    Node* q = new Node(p->str, p->freq, nullptr, p->left, p->right);
    Node* t = head;
    if (pr) {
        while(strcmp(t->str, pr->str)){
            if(t->next)
                t = t->next;
            else {
                std::cout << "Pr is not in list" << std::endl;
                return;
            }
        }
        if (!t->next){
            t->next = q;
        }
        q->next = t->next;
        t->next = q;
    }
} 

Code::Code(char* s) {
    int i, TAB[256] = { 0 }; // создание таблицы частот
    for (i = 0; s[i]; i++)
        TAB[s[i]]++;
    char p[2]; p[1] =  '\0';
    for (i = 0; i < 256 && TAB[i] == 0; i++)
        p[0] = i + 1;
    head = new Node(p, TAB[i]);
    i++;
    // формирование упорядоченного по частоте линейного списка символов строки s
    for( ; i < 256; i++) {
        if(TAB[i] != 0) {
            p[0] = i;
            if (TAB[i] < head->freq)
                AddToHead(p, TAB[i]);
            else {
                Node* t = head;
                while(t->next && t->next->freq <= TAB[i])
                    t = t->next;
                if(!t->next)
                    AddToTail(p, TAB[i]);
                else AddAfter(p, TAB[i], t);
            }
        }
    }
    type = 0;
}
void Code::FormTree() { // формирование списка в дерево
    if (!head) {
        std::cout << "List is empty!" << std::endl;
        return;
    }
    Node *p1, *p2, *q, *t; // p1, p2 - 2 узла, q - создаваемые узел, t - бегунок
    int n1, n2, fr;
    char* s;
    while(head->next) { // создание нового узла
        p1 = head;
        p2 = head->next;
        n1 = strlen(p1->str);
        n2 = strlen(p2->str);
        s = new char[n1 + n2 + 1];
        strcpy(s, p1->str);
        strcat(s, p2->str);
        fr = p1->freq + p2->freq;
        q = new Node(s, fr, nullptr, p1, p2);
        delete[] s;
        if(p2->next) {
            if(p2->next->freq == q->freq) {
                head = q; 
                head->next = p2->next;
                continue;
            }
        }
        head = p2->next;
        // размещение нового узла
        if (!head) head = q;
        else {
            t = head;
            while(t->next && t->next->freq < fr)
                t = t->next;
            if(!t->next) 
                AddToTail(q);
            else AddAfter(q, t);
        }
    }
    type = 1;
}

void Code::CodeText(char* s, char* code) {
    int i, TAB[256] = { 0 }; // создание таблицы частот
    for (i = 0; s[i]; i++)
        TAB[s[i]]++;
    char CodeTAB[256][10], ch;
    for (i = 0; i < 256; i++)
        CodeTAB[i][0] = '\0';
        // формирование таблицы ккодовых слов
    for (int i = 0; i < 256; i++)   {
        if (TAB[i]) {
            Node* t = head;
            while(t->left || t->right) {
                if (t->left && Find(i, t->left->str)) {
                    strcat(CodeTAB[i], "0");
                    t = t->left;
                }
                else {
                    strcat(CodeTAB[i], "1");
                    t = t->right;
                }
            }
        }
    }
        // формирование закодированного текста
    code[0] = '\0';
    for (i = 0; s[i]; i++) {
        strcat(code, CodeTAB[s[i]]);
    }
}

bool Code::Find(char ch, char* p) {
    for (int i = 0; p[i]; i++) {
        if (p[i] == ch)
            return true;
    }
    return false;
}

void Code::DecodeText(char* code, char* dcode) {
    Node* t;
    for (int i = 0; code[i];) {
        t = head;
        while(t->left && t->right){
            if (code[i] == '0'){
                t = t->left;
                i++;
                continue;
            }
            if (code[i] == '1'){    
                t = t->right;
                i++;
            }
        }
        strcat(dcode, t->str); 
    }
}

void Code::DelTree(Node* tree) {
    if (tree->left)  DelTree(tree->left);
    if (tree->right) DelTree(tree->right);
    delete tree;
    tree = nullptr;
}

Code::~Code() {
    if(type == 0) {
        while(head)
            DelHead();
    }
    else {
        DelTree(head);
    }
    delete head;
}

