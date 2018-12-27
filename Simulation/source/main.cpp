//
//  main.cpp
//  graph
//
//  Created by Foltányi Kolos on 2017. 11. 07..
//  Copyright © 2017. Foltányi Kolos. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include "Simulation.h"

int main(int argc, const char * argv[]) {
    Simulation sim("medium_graph.txt","medium_simulation.txt");
    sim.run();
    return 0;
}
