//  exceptions.h
//  Created by Foltányi Kolos on 2017. 11. 19..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
#ifndef exceptions_h
#define exceptions_h

#include <exception>

using namespace std;

class overflow_err : public exception//hashtable
{
public:
    const char* what() const throw() { return "Elfogyott a tábla területe!"; }
};

class invalid_key : public exception//hashtable
{
public:
    const char* what() const throw() { return "Ervenytelen kulcs!"; }
};

class invalid_condition : public exception//dbtable
{
public:
    const char* what() const throw() { return "Ervenytelen feltétel a joinban!"; }
};

class invalid_column_name : public exception//dbtable
{
public:
    const char* what() const throw() { return "Ervenytelen oszlopnev!"; }
};

class invalid_index: public exception//dbtable
{
public:
    const char* what() const throw() { return "Ervenytelen index!"; }
};

class invalid_value: public exception//dbtable
{
public:
    const char* what() const throw() { return "Ervenytelen érték!"; }
};
#endif /* exceptions_h */
