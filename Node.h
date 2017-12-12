/*
 * Node.h
 *
 *  Created on: Dec 12, 2017
 *      Author: czahacinschi
 */

#ifndef NODE_H_
#define NODE_H_

class Node
{
public:
    Node(int idx);
    virtual ~Node();

    int idx() const;

private:
    int idx_;
};

#endif /* NODE_H_ */
