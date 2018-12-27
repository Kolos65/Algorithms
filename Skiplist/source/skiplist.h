/**
 * -----------------------------------------------------------SKIPLIST----------------------------------------------------
 * skiplist.h
 *  Created on: 2017. okt. 16.
 *      Author: Foltányi Kolos FQTZ6K
 */
#ifndef SKIPLIST_H_
#define SKIPLIST_H_
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>

using namespace std;

class Node{
    public:
    int key;
    vector<Node*> next;
    Node(const int& data0) : key(data0){}
};

class Skiplist{
private:
	int counter;
	const int levels = 10;
	Node* min;
	Node* max;
	Node* cur;

public:
	Skiplist();
	~Skiplist();

	bool isEmpty();
	int size();
	bool contains(int x);
	vector<Node*> smallers(int x);

	void insert(int x);
	void erase(int x);

	void print();

};

//Constructor, destructor implementations
Skiplist::Skiplist(){
	counter = 0;
	min = new Node(INT_MIN);
	max = new Node(INT_MAX);
	for(int i=0;i<levels;i++){
		max->next.push_back(nullptr);
	}
	for(int i = 0;i<levels;i++){
		min->next.push_back(max);
	}
	cur = min;
    srand (time(NULL));
}

Skiplist::~Skiplist(){
	Node* tmp;
	for(Node* i=min; i!=nullptr;){
		tmp = i;
		i = i->next[0];
		delete tmp;
	}
}


// Functions to provide information about the list
bool Skiplist::isEmpty(){
	for(int i=0;i<levels;i++){
		if(min->next[i]!=max){
			return false;
		}
	}
	return true;
}


int Skiplist::size(){
	return counter;
}


bool Skiplist::contains(int x){
	vector<Node*> nodes = smallers(x);
	if(nodes[0]->next[0]->key==x){
		return true;
	}
	else{
		return false;
	}

}

/*
 Helper function that returns a vector containing every smaller element of the given value for each level.
 */
vector<Node*> Skiplist::smallers(int x){
	vector<Node*> smallers;
	cur=min;
	for(int i=levels-1;i>-1;){
			while(cur->next[i]->key < x && cur->next[i] != max){
				cur = cur->next[i];
			}
			smallers.push_back(cur);
			i--;
		}
	reverse(smallers.begin(),smallers.end());
	return smallers;

}


// List mutating functions:
void Skiplist::insert(int x){
	if(!contains(x)){
		counter++;
		Node* p = new Node(x);
		vector<Node*> nodes = smallers(x);
		bool chain = true;
		unsigned int i = 0;
		while(chain){
			p->next.push_back(nodes[i]->next[i]);
			nodes[i]->next[i]=p;
			int coin = rand() % 2;
			if(coin || i==nodes.size()-1){
				chain=false;
			}else{
				i++;
			}
		}
	}
}


void Skiplist::erase(int x){
	if(isEmpty()){
		//throw UnderFlowException();
		return;
	}
	if(!contains(x)){
		//throw InvalidElement();
		return;
	}
	vector<Node*> nodes = smallers(x);
	Node* tmp = nodes[0]->next[0];
	for(unsigned int i = 0;i<tmp->next.size();i++){
		nodes[i]->next[i]=tmp->next[i];
	}
	delete tmp;
	counter--;

}

//Debug purposes:
/*
 Prints the key of every element as many times as the number of levels the element is connected
*/
void Skiplist::print(){
	cout<<endl<<"SKIPLIST: "<<endl;
	cur=min->next[0];
	while(cur->next[0]!=nullptr){
		for(unsigned int i=0;i<cur->next.size();i++){
			cout<<cur->key<<' ';
		}
		cout<<endl;
		cur=cur->next[0];
	}
}



#endif /* SKIPLIST_H_ */
