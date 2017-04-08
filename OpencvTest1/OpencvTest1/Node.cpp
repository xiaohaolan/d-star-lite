#include "Node.h"

CNode::CNode(const CNode& cnode)
{

}

CNode::~CNode()
{
}

void CNode::operator=(const CNode& cnode)
{

}

IMPLEMENT_SERIAL(CNode, CObject, 1)

void CNode::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	
	if (ar.IsStoring())
	{
		ar << g << rhs << backPointnode;
	}
	else
	{
		ar >> g >> rhs >> backPointnode;
	}
}

