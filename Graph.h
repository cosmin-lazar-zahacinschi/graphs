/*
 * Graph.h
 *
 *  Created on: Dec 12, 2017
 *      Author: czahacinschi
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <istream>
#include <ostream>
#include <vector>

class Graph
{
public:
    Graph();
    virtual ~Graph();

    static Graph* createWithNodeCount(int count);
    static Graph* createFromInput(std::istream& in);

    void addEdge(int i, int j);
    int nodeCount() const;

    void show();

    Graph* makeSelfComplementary();
    Graph* makeInverse();

    struct GraphDifference
    {
        int nodeDiff;
        int edgeDiff;
        std::vector<std::pair<int, int>> extraEdges;
        std::vector<int> permutation;

        void output(std::ostream& out)
        {
            out << nodeDiff << " " << edgeDiff << std::endl;
            for(unsigned int i = 0; i < extraEdges.size(); i++)
            {
                out << extraEdges[i].first + 1 << " " << extraEdges[i].second + 1 << std::endl;
            }
            for(unsigned int i = 0; i < permutation.size(); i++)
            {
                out << permutation[i] + 1 << std::endl;
            }
        }

    };

    GraphDifference makeDifference(Graph* other);

private:
    bool** matrix_;
    int nodeCount_;
    int edgeCount_;
};

#endif /* GRAPH_H_ */
