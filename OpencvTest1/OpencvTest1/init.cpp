#include "Dlite.h"
#include "Node.h"



void CDlite::roadInit()
{
	endNode->rhs = 0;
	insert_to_opentable(endNode->x, endNode->y);
	openNodecount++;

	while (CalculateKey(openTable.front()) < CalculateKey(startNode) || startNode->rhs != startNode->g)
	{
		currNode = openTable.front();

		currNode->is_init = TRUE;

		if (currNode->x % 10 == 0 && currNode->y % 10 == 0)
		{
			cout << currNode->x << "," << currNode->y << endl;
		}

		if (currNode->g > currNode->rhs)
		{
			currNode->g = currNode->rhs;
			getPrednodes(currNode->x, currNode->y);
		}
		else
		{
			currNode->g = INT_MAX;
			getPrednodes(currNode->x, currNode->y);
			updateVertex(currNode->x, currNode->y);
		}

		//currNode->is_in_closetable = TRUE;
		delete_from_opentable(currNode->x, currNode->y);
		openTable.sort(Cmpare());
	}

}

void CDlite::nodeSerialization()
{
	char buf[5120];
	int i, j;

	// 序列化
	CFile fileStore;
	if (fileStore.Open(_T("initResult.dat"), CFile::modeWrite | CFile::modeCreate))
	{
		CArchive arStore(&fileStore, CArchive::store, 5120, buf);
		
		for (i = 0; i<MAPHEIGHT; i++)
		{
			for (j = 0; j < MAPWIDTH; j++)
			{
				arStore << &node[i][j];
			}
			if (i % 50 == 0)
			{
				cout << i/10 << "% 存储中……" << endl;
			}
		}

		arStore.Close();
		fileStore.Close();
	}

	cout << "存储成功" << endl;

}

void CDlite::nodeDeSerialization()
{
	char buf[5120];
	int i, j;

	CFile fileLoad;
	if (fileLoad.Open(_T("initResult.dat"), CFile::modeRead))
	{
		CArchive arLoad(&fileLoad, CArchive::load, 5120, buf);
		CNode* pNodeLoad = new CNode;

		for (i = 0; i<MAPHEIGHT; i++)
		{
			for (j = 0; j < MAPWIDTH; j++)
			{
				arLoad >> pNodeLoad;
				node[i][j] = *pNodeLoad;
			}
			if (i % 20 == 0)
			{
				cout << i / 10 << "% 读取中……" << endl;
			}
		}
		arLoad.Close();
	}

	fileLoad.Close();

	cout << "读取成功" << endl;
}