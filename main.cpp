/*
 * main.cpp
 *
 *  Created on: Dec 12, 2017
 *      Author: czahacinschi
 */

#include <iostream>
#include <fstream>

#include "Graph.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "No input!" << std::endl;
        return 1;
    }

    std::fstream fin;
    fin.open(argv[1], std::fstream::in);

    if(!fin.is_open())
    {
        std::cerr << "Cannot open " << argv[1] << " !" << std::endl;
        return 1;
    }

    Graph* g = Graph::createFromInput(fin);

    Graph* large = g->makeSelfComplementary();

    Graph::GraphDifference diff = g->makeDifference(large);

    std::fstream fout;
    fout.open("output/03_BOS.txt", std::fstream::out);

    diff.output(fout);
    fout.close();
    return 0;
}


