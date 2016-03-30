/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Map.h"

class Graph {
private:
	vector<vector<Node *> > nodes;

public:
	void buildGraphFromMap(const Map &map);
	Graph();
	virtual ~Graph();
};

#endif /* GRAPH_H_ */
