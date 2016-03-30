/*
 * Node.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

enum Direction { LEFT, RIGHT, UP, DOWN };
#define DIRECTIONS_NUM 4

class Node {
private:
	int row;
	int col;
	vector<Node *> neighbors;

public:
	Node();
	virtual ~Node();
};

#endif /* NODE_H_ */
