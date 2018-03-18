#include <iostream>

using namespace std;

class Node {
public:
	Node(double a);
	void Link(Node* a, Node* b);
	double Pop();
	double Read();
	Node* Next();
	Node* Left();
private:
	Node *Nextr, *Nextl;
	double elem;

};

class Stack {
public:
	Stack();
	double Push(double a);
	double Pop();
	double Read();
	int size();
private:
	Node  *now;
	int sz;
};

Node::Node(double a) :
	elem{ a }, Nextr{ '\0' }, Nextl{ '\0' } {}

void Node::Link(Node* a, Node* b) {
	Nextr = a;
	a->Nextl = b;
}

double Node::Pop() {
	return elem;
}

Node* Node::Next() {
	return Nextr;
}

Node* Node::Left() {
	return Nextl;
}

double Node::Read() {
	return elem;
}

Stack::Stack() :
	now{ new Node(0) },sz{ 0 } {}

double Stack::Push(double a) {
	if (sz == 0) {
		delete(now);
		now = new Node(a);
	}
	else {
		now->Link(new Node(a), now);
		now = now->Next();
	}

	sz++;

	return a;
}

double Stack::Pop() {
	double a;
	Node *buf;
	if (sz == 0)
		return 0;
	else
		a = now->Pop();
	buf = now;
	now = now->Left();
	if (sz != 1)
		delete buf;
	sz--;
	return a;
}

double Stack::Read() {
	if (sz == 0)
		return 0;
	return now->Read();
}

int Stack::size() {
	return sz;
}
