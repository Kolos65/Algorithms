//
//  main.cpp
//  sorternet
//
//  Created by Foltányi Kolos on 2017. 12. 09..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>
using namespace std;

template<typename T>
void swapit(T& a, T& b) {
    T t = a;
    a = b;
    b = t;
}


template<typename T>
void rendez_blokkot(T *tomb, int meret, bool direction){
    for(int i=0;i<meret/2;i++){
        int j = i+meret/2;
        if(direction){
            if(tomb[i]>tomb[j]){
                swapit<T>(tomb[i],tomb[j]);
             }
        }else{
            if(tomb[i]<tomb[j]){
                swap(tomb[i],tomb[j]);
             }
        }
    }
}


template<typename T>
void rendez(T *tomb, int meret, bool direction){
    if(meret<1){
        return;
    }else{
        rendez<T>(tomb, meret/2, true);
        rendez<T>(&tomb[meret/2], meret/2, false);
    }
    
    int steps = log2(meret);
    for(int i=0;i<steps;i++){
        int blocks = pow(2,i);
        int blocksize = meret/blocks;
        for(int j=0;j<blocks;j++){
                rendez_blokkot<T>(&tomb[j*blocksize], blocksize, direction);
        }
    }
}


template <typename T>
void rendezo_halozat(T *tomb, int meret){
    rendez(tomb,meret,true);
}



int main(int argc, const char * argv[]) {
    
    int size=32;
    int numbers[size];
    srand(static_cast<unsigned int>(time(0)));
    for(int i=0;i<size;i++){
        numbers[i] = rand()%100 / 5.4;
    }
    cout<<"Eredeti:"<<endl;
    for(int i:numbers){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"Rendzett:"<<endl;
    
    rendezo_halozat<int>(numbers, size);
    
    for(int i:numbers){
        cout<<i<<" ";
    }
    cout<<endl<<endl;
}



