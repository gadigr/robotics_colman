/*
 * Point.h
 *
 *  Created on: May 27, 2014
 *      Author: user
 */

#ifndef POINT_H_
#define POINT_H_

#include <utility>

using namespace std;

class Point : public pair<double,double>
{
public:
	Point()
	{

	}

	Point(double x, double y) : pair<double,double>(x, y)
	{
	}

	double getX() const
	{
		 return first;
	}

	double getY() const
	{
		 return second;
	}

	void setX(double x)
	{
		 first = x;
	}

	void setY(double y)
	{
		 second = y;
	}

	virtual ~Point()
	{

	}
};

#endif /* POINT_H_ */
