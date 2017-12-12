/*
 * Graph.cpp
 *
 *  Created on: Dec 12, 2017
 *      Author: czahacinschi
 */

#include "Graph.h"

#include <iostream>
#include <string>
#include <sstream>

Graph::Graph() :
        matrix_(nullptr), nodeCount_(0), edgeCount_(0)
{
    // TODO Auto-generated constructor stub

}

Graph::~Graph()
{
    // TODO Auto-generated destructor stub
}

Graph* Graph::createWithNodeCount(int count)
{
    Graph* g = new Graph;
    g->matrix_ = new bool*[count];
    for (int i = 0; i < count; i++)
    {
        g->matrix_[i] = new bool[count];
        for (int j = 0; j < count; j++)
        {
            g->matrix_[i][j] = false;
        }
    }
    g->nodeCount_ = count;
    return g;
}

Graph* Graph::createFromInput(std::istream& in)
{

    std::string line;
    std::getline(in, line);

    std::istringstream iss(line);
    std::string temp;

    iss >> temp;
    int nodeCount = std::stoi(temp);
    iss >> temp;
    int edgeCount = std::stoi(temp);

    Graph* g = Graph::createWithNodeCount(nodeCount);
    for (int i = 0; i < edgeCount; i++)
    {
        std::getline(in, line);
        std::istringstream iss(line);

        iss >> temp;
        int first = std::stoi(temp);
        iss >> temp;
        int second = std::stoi(temp);

        g->addEdge(first - 1, second - 1);
    }

    return g;
}

void Graph::addEdge(int i, int j)
{
    matrix_[i][j] = true;
    matrix_[j][i] = true;
    edgeCount_++;
}

void Graph::show()
{
    std::cout << "Node count: " << nodeCount_ << std::endl;
    for (int i = 0; i < nodeCount_; i++)
    {
        for (int j = 0; j < nodeCount_; j++)
        {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Graph* Graph::makeSelfComplementary()
{
    Graph* g = Graph::createWithNodeCount(nodeCount_ * 4);

    for (int i = 0; i < nodeCount_; i++)
    {
        for (int j = 0; j < nodeCount_; j++)
        {
            if ( i == j ) continue;
            if ( !matrix_[i][j] )
            {
                g->addEdge(i + nodeCount_, j + nodeCount_);
                g->addEdge(i + 2 * nodeCount_, j + 2 * nodeCount_);
            }
            else
            {
                g->addEdge(i, j);
                g->addEdge(i + 3 * nodeCount_, j + 3 * nodeCount_);

            }
        }
    }

    for (int i = 0; i < nodeCount_; i++)
    {
        for (int j = nodeCount_; j < 2 * nodeCount_; j++)
        {
            g->addEdge(i, j);
        }
    }
    for (int i = nodeCount_; i < 2 * nodeCount_; i++)
    {
        for (int j = 2 * nodeCount_; j < 3 * nodeCount_; j++)
        {
            g->addEdge(i, j);
        }
    }
    for (int i = 2 * nodeCount_; i < 3 * nodeCount_; i++)
    {
        for (int j = 3 * nodeCount_; j < 4 * nodeCount_; j++)
        {
            g->addEdge(i, j);
        }
    }

    return g;
}

Graph* Graph::makeInverse()
{
    Graph* g = Graph::createWithNodeCount(nodeCount_);
    for (int i = 0; i < nodeCount_; i++)
    {
        for (int j = 0; j < nodeCount_; j++)
        {
            if ( i != j )
            {
                if ( !matrix_[i][j] )
                {
                    g->addEdge(i, j);
                }
            }
        }
    }
    return g;
}

Graph::GraphDifference Graph::makeDifference(Graph* other)
{
    GraphDifference diff;

    diff.nodeDiff = other->nodeCount_ - nodeCount_;
    diff.edgeDiff = 3 * nodeCount_ * nodeCount_ + edgeCount_ + 2 * (nodeCount_ * (nodeCount_ - 1) / 2 - edgeCount_);
    for (int i = 0; i < other->nodeCount_ - 1; i++)
    {
        for (int j = i + 1; j < other->nodeCount_; j++)
        {
            bool different = false;
            if ( i >= nodeCount_ || j >= nodeCount_ )
            {
                different = true;
            }
            else
            {
                if ( matrix_[i][j] == false && other->matrix_[i][j] == true )
                {
                    different = true;
                }
            }
            if ( different && other->matrix_[i][j] )
            {
                diff.extraEdges.emplace_back(std::make_pair(i, j));
            }
        }
    }

    for (int i = 0 + 1 * nodeCount_; i < 2 * nodeCount_; i++)
    {
        diff.permutation.emplace_back(i);
    }
    for (int i = 0 + 3 * nodeCount_; i < 4 * nodeCount_; i++)
    {
        diff.permutation.emplace_back(i);
    }
    for (int i = 0 + 0 * nodeCount_; i < 1 * nodeCount_; i++)
    {
        diff.permutation.emplace_back(i);
    }
    for (int i = 0 + 2 * nodeCount_; i < 3 * nodeCount_; i++)
    {
        diff.permutation.emplace_back(i);
    }

    return diff;
}
