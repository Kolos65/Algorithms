//  hashtable.h
//  Created by Foltányi Kolos on 2017. 11. 19..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
#ifndef hashtable_h
#define hashtable_h
#include <list>
#include <vector>
#include "exceptions.h"


class IntFingerprint{
public:
    int operator()(int key){
        return key ;
    }
};

class StringFingerprint{
public:
    int operator()(const std::string & key){
        unsigned h = 0 ;
        for (unsigned int i = 0; i < key.size(); ++i){
            h += (256 * h + key[i]) % 16777213 ;
        }
        return int(h);
    }
};

template <class Key, class Fingerprint, class Data>
class HashTable
{
    enum state_t{
        FREE,
        ERASED,
        USED
    };
    
    struct Node{
        Key key ;
        Data data;
        state_t state ;
        Node() : state(FREE) {}
    } ;
   
    const int logtablesize;
    const int tablesize;
    
    int actualsize;
    
    std::vector<Node> table;
    
    Fingerprint fingerprint;
    
    int getHash(const Key & key, int i){
        static const unsigned s = 2654435769U; // == 2**32 * (sqrt(5) - 1)/2
        unsigned k = fingerprint(key);
        unsigned h = (k * s) >> (32 - logtablesize);
        return (h + i) % tablesize;
    }
    
    static int round_tablesize(int _tablesize){
        int i = 4;
        while ((1<<i) < _tablesize){
            ++i;
        }
        return i;
    }
public:
    HashTable(int _tablesize) :
    logtablesize(round_tablesize(_tablesize)),
    tablesize(1 << logtablesize),
    actualsize(0),
    table(tablesize)
    {}
    
    int size(){
        return actualsize ;
    }
    
    bool empty(){
        return actualsize == 0 ;
    }
    
    void clear(){
        for (int i = 0; i < tablesize; ++i){
            table[i].state = FREE;
        }
    }
    
    void insert(const Key & key, Data data_){
        for (int i = 0; i < tablesize; ++i){
            int pos = getHash(key, i);
            if (table[pos].state != USED){
                table[pos].key = key;
                table[pos].data = data_;
                table[pos].state = USED;
                ++actualsize;
                return;
            }
            else if (table[pos].key == key){
                return ;
            }
        }
        throw overflow_err();
    }

    bool find(const Key & key){
        for (int i = 0; i < tablesize; ++i){
            int pos = getHash(key, i) ;
            
            if (table[pos].state == FREE){
                return false;
            }
            else if (table[pos].state == USED && table[pos].key == key){
                return true;
            }
        }
        
        return false ;
    }
    
    void erase(const Key & key){
        for (int i = 0; i < tablesize; ++i){
            int pos = getHash(key, i) ;
            
            if (table[pos].state == FREE)
            {
                break;
            }
            else if (table[pos].state == USED && table[pos].key == key)
            {
                table[pos].state = ERASED;
                actualsize--;
                break;
            }
        }
    }
    
    Data operator[](const Key & key){
        for (int i = 0; i < tablesize; ++i){
            int pos = getHash(key, i) ;
            
            if (table[pos].state == FREE){
                throw invalid_key();
            }
            else if (table[pos].state == USED && table[pos].key == key){
                return table[pos].data;
            }
        }
        throw invalid_key();
    }
    
    void print()
    {
        for (int i = 0; i < tablesize; ++i)
        {
            std::cout << i << ": " ;
            if (table[i].state == USED)
            {
                std::cout << table[i].key ;
            }
            else if (table[i].state == ERASED)
            {
                std::cout << "-T-";
            }
            std::cout << std::endl ;
        }
    }
} ;


#endif /* hashtable_h */
