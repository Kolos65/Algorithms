
//  graph.h
//  Created by Foltányi Kolos on 2017. 11. 07..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;

class Node{
public:
    int key;
    vector<Node*> next;
    vector<int> nextkeys;
    vector<int> costs;
    Node(const int& key):key(key){}
};

class Graph{
public:
    int numberofnodes;
    int numberofstorage;
    vector<int> storagekeys;
    vector<Node*> nodes;
    
    Graph(string graphfilename);
    ~Graph();
    void print();
};

Graph::Graph(string graphfilename){
    string line;
    ifstream f (graphfilename);
    if (f.is_open()){
        
        getline(f,line);
        numberofnodes = stoi(line);
        
        for(int i=0;i<numberofnodes;i++){
            getline(f,line);
            stringstream ss(line);
            int tmp;
            ss >> tmp;
            Node* node = new Node(tmp);
            
            while (ss >> tmp){
                node->nextkeys.push_back(tmp);
                if (ss.peek() == ' '){
                    ss.ignore();
                }
                ss >> tmp;
                node->costs.push_back(tmp);
                if (ss.peek() == ' '){
                    ss.ignore();
                }
            }
            nodes.push_back(node);
        }
        
        for(size_t i=0;i<nodes.size();i++){
            for(size_t j=0;j<nodes[i]->nextkeys.size();j++){
                nodes[i]->next.push_back(nodes[nodes[i]->nextkeys[j]]);
            }
        }
        
        getline(f,line);
        numberofstorage = stoi(line);
        
        for(int i=0;i<numberofstorage;i++){
            getline(f,line);
            storagekeys.push_back(stoi(line));
        }
        
        f.close();
    }
    else{
        cerr << "Unable to open file" << '\n';
    }
}


Graph::~Graph(){
    for(size_t i=0;i<nodes.size();i++){
        delete nodes[i];
    }
}



void Graph::print(){
    cout<<"----------------------------GRAPH:-------------------------------"<<endl<<endl;
    cout<<numberofnodes<<" db Node-bol all:"<<endl<<endl;
    for(size_t i=0;i<nodes.size();i++){
        ///NODE
        cout<<nodes[i]->key<<". Node:"<< '\n'<<'\n';
        ///NEXTKEYS
        cout<<"nextkeysvector: ";
        for(size_t j=0;j<nodes[i]->nextkeys.size();j++){
            cout<<nodes[i]->nextkeys[j]<<' ';
        }
        cout<<endl;
        ///NEXT
        cout<<"nextvector:     ";
        for(size_t j=0;j<nodes[i]->next.size();j++){
            cout<<nodes[i]->next[j]->key<<' ';
        }
        cout<<endl;
        ///COST
        cout<<"cost:           ";
        for(size_t j=0;j<nodes[i]->costs.size();j++){
            cout<<nodes[i]->costs[j]<<' ';
        }
        cout<<endl;
        cout<<endl;
    }
    cout<<"raktarak szama"<<numberofstorage<<", key-ek: ";
    for(int i=0;i<numberofstorage;i++){
        cout<<storagekeys[i]<<' ';
    }
    cout<<endl<<"-------------------------VEGE---------------------------"<<endl;
}



#endif /* Graph_h */

