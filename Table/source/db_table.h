//
//  db_table.h
//  table
//
//  Created by Foltányi Kolos on 2017. 11. 19..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
//
#ifndef db_table_h
#define db_table_h
#include <algorithm>
#include <locale>
#include <string>
#include <sstream>
#include <iostream>
#include "hashtable.h"
#include "exceptions.h"
using namespace std;

class db_table{
private:
    vector<string> columnnames;
    vector<vector<string>> table;
    int rows;
    int columns;
    
    
public:
    db_table();
    void add_column(string name);
    vector<string> column_names();
    void add_row();
    int row_count();
    int column_count();
    void set(string col, size_t row, string value);
    string get(string col, size_t row);
    string keygenerator(vector<string> cond,int i);
    db_table join(db_table& other, string cond);
};

db_table::db_table():rows(0),columns(0){}

void db_table::add_column(string name){
    bool contains = columnnames.end() != find(columnnames.begin(), columnnames.end(), name);
    bool notaplhanumeric = name.end() != find_if(begin(name), end(name), [](char c) {return !isalnum(c);});
    bool empty = name.empty();
    if(contains || notaplhanumeric || empty){
        throw invalid_column_name();
    }
    columnnames.push_back(name);
    vector<string> tmp(rows,"");
    table.push_back(tmp);
    columns++;
}


vector<string> db_table::column_names(){
    return columnnames;
}


void db_table::add_row(){
    for(int i = 0; i<table.size();i++){
        table[i].push_back("");
    }
    rows++;
}


int db_table::row_count(){
    return rows;
}

int db_table::column_count(){
    return columns;
}


void db_table::set(string col, size_t row, string value){
    vector<string>::iterator it = find(columnnames.begin(), columnnames.end(), col);
    size_t pos = it-columnnames.begin();
    if(pos>=columns||row>=rows){
        throw invalid_index();
    }
    if(value.end()!=find_if(value.begin(), value.end(), [](char c) {return c=='\0';})){
        throw invalid_value();
    }
    table[pos][row]=value;
    
}


string db_table::get(string col, size_t row){
    vector<string>::iterator it = find(columnnames.begin(), columnnames.end(), col);
    size_t pos = it-columnnames.begin();
    if(pos>=columns||row>=rows){
        throw invalid_index();
    }
    return table[pos][row];
}

string db_table::keygenerator(vector<string> cond,int i){
    string key;
    for(int j=0;j<cond.size();j++){
        size_t pos = find(columnnames.begin(), columnnames.end(), cond[j]) - columnnames.begin();
        if(pos>=columns){
            throw invalid_condition();
        }
        key+=table[pos][i];
        key+='\0';
    }
    return key;
}

db_table db_table::join(db_table& other, string cond){
    if(cond[cond.size()-1]==','||other.row_count()==0||rows==0){
        throw invalid_condition();
    }
    db_table result;
    for(int i=0;i<columns;i++){
        result.add_column(columnnames[i]);
    }
    for(int i=0;i<other.column_count();i++){
        result.add_column(other.column_names()[i]);
    }
    vector<string> cond1;
    vector<string> cond2;
    stringstream ss(cond);
    string pairs;
    while(getline(ss, pairs, ',')){
        stringstream cc(pairs);
        string tmp;
        getline(cc, tmp, '=');
        cond1.push_back(tmp);
        getline(cc, tmp);
        cond2.push_back(tmp);
    }
    HashTable<string, StringFingerprint, int> hashtable(rows);
    for(int i=0;i<rows;i++){
        string key = keygenerator(cond1, i);
        int data = i;
        hashtable.insert(key, data);
    }
    for(int i=0;i<other.row_count();i++){
        string key = other.keygenerator(cond2, i);
        if(hashtable.find(key)){
            result.add_row();
            for(int j=0;j<columns;j++){
                result.set(columnnames[j], result.row_count()-1, table[j][hashtable[key]]);
            }
            for(int j=0;j<other.column_count();j++){
                result.set(other.column_names()[j],result.row_count()-1, other.get(other.column_names()[j], i));
            }
        }
    }
    return result;
}

#endif /* db_table_h */
