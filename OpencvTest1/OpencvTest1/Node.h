#pragma once
#include <afxwin.h>
#include <math.h>

#define VACANT 0
#define BARRIER 1
#define STARTNODE 2
#define ENDNODE 3

class CNode : public CObject
{
public:

	DECLARE_SERIAL(CNode)

	int x;
	int y;
	int z;

	int g;
	int rhs;

	int type;

	bool is_init;
	bool is_on_road;
	bool is_in_closetable;
	bool is_in_opentable;
	CNode *backPointnode;

public:
	
	CNode(){};
	CNode(const CNode& cnode);

	void operator=(const CNode& cnode);
	~CNode();

	void Serialize(CArchive &); 
};

