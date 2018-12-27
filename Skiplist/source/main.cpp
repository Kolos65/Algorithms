//
//  main.cpp
//  skiplist
//
//  Created by Foltányi Kolos on 2017. 10. 23..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
//

#include <iostream>
#include "skiplist.h"


int main(int argc, const char * argv[]) {
    Skiplist s;
    for(int i=0;i<10000;i++){
        s.insert(i);
    }
    s.print();
    return 0;
}






