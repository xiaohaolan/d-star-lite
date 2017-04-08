#pragma once
#include "Node.h"

class Cmpare
{
public:
	Cmpare();
	~Cmpare();
	//int h(const CNode* nd1, const CNode* nd2) const;
	bool operator()(const CNode* nd1, const CNode* nd2) const;

};