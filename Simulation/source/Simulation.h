//  Simulation.h
//  Created by Foltányi Kolos on 2017. 11. 08..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
#ifndef Simulation_h
#define Simulation_h

#include "Graph.h"

struct Product{
    int destinationnode;
    int size;
    bool operator <(const Product& x){
        return size<x.size;
    }
    bool operator >(const Product& x){
        return size>x.size;
    }
};

bool sorterp (Product* i,Product* j) {return (*i < *j);}

struct Truck{
    int capacity;
    int startingnode;
    vector<Product*> products;
    vector<vector<int>> routes;
    vector<int> distances;
    bool operator <(const Truck& x){
        return capacity<x.capacity;
    }
    bool operator >(const Truck& x){
        return capacity>x.capacity;
    }
};

bool sortert (Truck* i,Truck* j) {return (*i < *j);}

class Simulation{
private:
    int numberoftrucks;
    int numberofproducts;
    vector<Truck*> trucks;
    vector<Product*> products;
    vector<Product*> leftovers;
    const Graph* simgraph;
    
public:
    Simulation(string graphfilename,string simulationfilename);
    ~Simulation();
    vector<int> dijkstra(int start,int finish);
    void loadtrucks();
    void run();
};

Simulation::Simulation(string graphfilename,string simulationfilename){
    simgraph = new Graph(graphfilename);
    string line;
    ifstream f (simulationfilename);
    if(f.is_open()){
        getline(f,line);
        numberoftrucks = stoi(line);
        for(int i=0;i<numberoftrucks;i++){
            Truck* truck = new Truck();
            int tmp;
            getline(f,line);
            stringstream ss(line);
            ss>>tmp;
            truck->capacity=tmp;
            if (ss.peek() == ' '){
                ss.ignore();
            }
            ss>>tmp;
            truck->startingnode=tmp;
            trucks.push_back(truck);
        }
        getline(f,line);
        numberofproducts = stoi(line);
        for(int i=0;i<numberofproducts;i++){
            Product* product = new Product();
            int tmp;
            getline(f,line);
            stringstream ss(line);
            ss>>tmp;
            product->destinationnode=tmp;
            if (ss.peek() == ' '){
                ss.ignore();
            }
            ss>>tmp;
            product->size=tmp;
            products.push_back(product);
        }
        f.close();
    }
    else{
        cerr << "Unable to open file" << '\n';
    }
}


Simulation::~Simulation(){
    for(int i=0;i<numberoftrucks;i++){
        delete trucks[i];
    }
    for(int i=0;i<numberofproducts;i++){
        delete products[i];
    }
    delete simgraph;
}



vector<int> Simulation::dijkstra(int start, int finish){
    int lengthofpath=0;
    vector<int> laststeps(simgraph->numberofnodes,INT_MAX);
    laststeps[start]=start;
    vector<int> keys;
    for(int i=0;i<simgraph->numberofnodes;i++)
        keys.push_back(simgraph->nodes[i]->key);
    vector<int> dist(simgraph->numberofnodes,INT_MAX);
    dist[start]=0;
    Node* cur;
    for(int i=0;i<simgraph->numberofnodes;i++){
        int minval = INT_MAX;
        unsigned long minindex=start;
        for(size_t k=0;k<dist.size();k++){
            if(dist[k]<minval){
                minval=dist[k];
                minindex=k;
            }
        }
        if(finish==keys[minindex]){
            lengthofpath=minval;
            break;
        }
        cur=simgraph->nodes[keys[minindex]];
        int curcost = dist[minindex];
        dist.erase(dist.begin()+minindex);
        keys.erase(keys.begin()+minindex);
        
        for(size_t j=0;j<cur->nextkeys.size();j++){
            unsigned long distindex=j;
            bool canberefreshed=false;
            for(size_t l=0;l<keys.size();l++){
                if(keys[l]==cur->nextkeys[j]){
                    canberefreshed=true;
                    distindex=l;
                }
            }
            
            if(canberefreshed && cur->costs[j] + curcost < dist[distindex]){
                dist[distindex] = cur->costs[j] + curcost;
                laststeps[keys[distindex]] = cur->key;
            }
        }
    }
    
    vector<int> solution;
    solution.push_back(finish);
    int tmp = finish;
    while(tmp!=start){
        solution.push_back(laststeps[tmp]);
        tmp=laststeps[tmp];
    }
    reverse(solution.begin(),solution.end());
    solution.push_back(lengthofpath);
    return solution;
}


void Simulation::loadtrucks(){
    
    sort(products.begin(), products.end(), sorterp);

    sort(trucks.begin(), trucks.end(), sortert);

    unsigned int index=0;
    for(int i=0;i<numberoftrucks;i++){
        int sum=0;

        while(index<products.size() && !(sum+products[index]->size > trucks[i]->capacity)){
            trucks[i]->products.push_back(products[index]);
            sum+=products[index]->size;
            index++;
        }
    }

    if(index<products.size()-1){
        for(int i=index;i<numberofproducts;i++){
            leftovers.push_back(products[i]);
        }
    }
    
    for(int i=0;i<numberoftrucks;i++){
        for(unsigned int j=0;j<trucks[i]->products.size();j++){
            vector<int> tmp;
            if(j==0){
                tmp = dijkstra(trucks[i]->startingnode, trucks[i]->products[0]->destinationnode);
            }
            else{
                tmp = dijkstra(trucks[i]->products[j-1]->destinationnode, trucks[i]->products[j]->destinationnode);
            }

            trucks[i]->distances.push_back(tmp[tmp.size()-1]);

            tmp.pop_back();
            trucks[i]->routes.push_back(tmp);
        }
    }
}


void Simulation::run(){
    loadtrucks();
    for(int i=0;i<numberoftrucks;i++){
        cout<<"A "<<trucks[i]->capacity<<" kapacitasu kamion, a "<<trucks[i]->startingnode<<" szamu raktarbol indul:"<<endl;
        for(unsigned int j=0;j<trucks[i]->products.size();j++){

            cout<<"   "<<trucks[i]->products[j]->destinationnode<<". helyre szallit "<<trucks[i]->products[j]->size<<" meretu csomagot, megtett ut: "<<trucks[i]->distances[j];

            cout<<" (utvonal: ";
            for(size_t k=0;k<trucks[i]->routes[j].size();k++){
                cout<<trucks[i]->routes[j][k];
                if(k!=trucks[i]->routes[j].size()-1)
                    cout<<"->";
            }
            cout<<")"<<endl;
        }
        cout<<endl;
    }
    
    cout<<"A raktarban maradt "<<leftovers.size()<<" termek:"<<endl;
    for(size_t i=0;i<leftovers.size();i++){
        cout<<"    "<<leftovers[i]->destinationnode<<". helyre kuldott, "<<leftovers[i]->size<<" meretu"<<endl;
    }
    
}

#endif /* Simulation_h */

