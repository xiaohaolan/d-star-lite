#include "Cmpare.h"

Cmpare::Cmpare()
{
}
Cmpare::~Cmpare()
{
}
/*
int Cmpare::h(const CNode* nd1, const CNode* nd2) const
	{
		int dis;

		dis = (int)sqrt(pow((double)abs(nd1->x - nd2->x), 2) + pow((double)abs(nd1->y - nd2->y), 2));

		return dis;
	}

	*/
bool Cmpare::operator()(const CNode* nd1, const CNode* nd2) const
{
		/*int key_a1, key_a2, key_b1, key_b2;

		key_a1 = min(nd1->g, nd1->rhs) + h(startNode, nd1);
		key_a2 = min(nd1->g, nd1->rhs);

		key_b1 = min(nd2->g, nd2->rhs) + h(startNode, nd2);
		key_b2 = min(nd2->g, nd2->rhs);

		if (key_a1 >= key_b1 && key_a2 > key_b2)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}*/
	return nd1->rhs < nd2->rhs;
}