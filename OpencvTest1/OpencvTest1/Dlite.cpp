#include "Dlite.h"


CDlite::CDlite()
{
}

CDlite::~CDlite()
{
}

void CDlite::pathPlanning()
{
	start = clock();

	mapInit();
	

	startNode = &node[start_x][start_y];
	endNode = &node[end_x][end_y];

	if (startNode->x == endNode->x && startNode->y == endNode->y)
	{
		cout << "起点=终点\n" << endl;
		
		return;
	}

	roadInit();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout <<"用时"<< duration <<"s"<< endl;
	
	//nodeSerialization();
	drawWindow();
	//nodeDeSerialization();
//	readMap();
}

int CDlite::readMap()
{
	//读取地图文件map.txt

	fstream map("map.txt");
	if (!map.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	char buffer[MAPWIDTH * 2];
	int i = 0, j = 0;
	while (!map.eof())
	{
		map.getline(buffer, MAPWIDTH * 2);

		for (j = 0; j < MAPWIDTH; j++)
		{
			if (buffer[j] == BARRIER)
			{
				node[i][j].type = BARRIER;
			}
		}
		i++;
	}

	return 0;
}

void CDlite::drawWindow()
{
	const char atom_window[16] = "Drawing 1: Atom";
	int i, j;

	for (i = 0; i<MAPHEIGHT; i++)
	{
		for (j = 0; j < MAPWIDTH; j++)
		{
			if (node[i][j].is_init == TRUE)
			{
				MyFilledCircle(atom_image, Point(i, j), Scalar(240, 251, 255));
			}
		}
	}

	MyFilledCircle(atom_image, Point(start_x, start_y), Scalar(255, 0, 0));
	MyFilledCircle(atom_image, Point(end_x, end_y), Scalar(0, 0, 255));

	imshow(atom_window, atom_image);
	cvMoveWindow(atom_window, 200, 0);
}

void CDlite::mapInit()
{
	int i, j;

	for (i = 0; i < MAPHEIGHT; i++)
	{
		for (j = 0; j < MAPWIDTH; j++)
		{
			node[i][j].x = i;
			node[i][j].y = j;
			node[i][j].z = 0;
			node[i][j].g = INT_MAX;
			node[i][j].rhs = INT_MAX;
			node[i][j].is_in_closetable = 0;
			node[i][j].is_in_opentable = 0;
			node[i][j].type = VACANT;
			node[i][j].backPointnode = &node[0][0];
		}
	}

	node[start_x][start_y].type = STARTNODE;
	node[end_x][end_y].type = ENDNODE;
}

int CDlite::CalculateKey(CNode * node)
{
	return node->rhs;
}

void CDlite::insert_to_opentable(int x, int y)
{
	node[x][y].is_in_opentable = TRUE;
	openTable.insert(openTable.end(), &node[x][y]);
	openNodecount++;
}

void CDlite::getPrednodes(int x,int y)
{
	if ((x + 1) >= 0 && (x + 1)<MAPWIDTH && y >= 0 && y<MAPHEIGHT && !node[x + 1][y].is_in_closetable)
	{
		updateVertex(x + 1, y);
	}

	if ((x - 1) >= 0 && (x - 1)<MAPWIDTH && y >= 0 && y<MAPHEIGHT && !node[x - 1][y].is_in_closetable)
	{
		updateVertex(x - 1, y);
	}

	if (x >= 0 && x<MAPWIDTH && (y + 1) >= 0 && (y + 1)<MAPHEIGHT && !node[x][y + 1].is_in_closetable)
	{
		updateVertex(x, y + 1);
	}

	if (x >= 0 && x<MAPWIDTH && (y - 1) >= 0 && (y - 1)<MAPHEIGHT && !node[x][y - 1].is_in_closetable)
	{
		updateVertex(x, y - 1);
	}

	if ((x + 1) >= 0 && (x + 1)<MAPWIDTH && (y + 1) >= 0 && (y + 1)<MAPHEIGHT && !node[x + 1][y + 1].is_in_closetable)
	{
		updateVertex(x + 1, y + 1);
	}

	if ((x + 1) >= 0 && (x + 1)<MAPWIDTH && (y - 1) >= 0 && (y - 1)<MAPHEIGHT && !node[x + 1][y - 1].is_in_closetable)
	{
		updateVertex(x + 1, y - 1);
	}

	if ((x - 1) >= 0 && (x - 1)<MAPWIDTH && (y + 1) >= 0 && (y + 1)<MAPHEIGHT && !node[x - 1][y + 1].is_in_closetable)
	{
		updateVertex(x - 1, y + 1);
	}

	if ((x - 1) >= 0 && (x - 1)<MAPWIDTH && (y - 1) >= 0 && (y - 1)<MAPHEIGHT && !node[x - 1][y - 1].is_in_closetable)
	{
		updateVertex(x - 1, y - 1);
	}
}

void CDlite::updateVertex(int x, int y)
{
	if (node[x][y].type != ENDNODE)
	{
		getSuccnodes(x, y);
	}
	if (node[x][y].is_in_opentable)
	{
		delete_from_opentable(x, y);
	}

	if (node[x][y].g != node[x][y].rhs)
	{
		insert_to_opentable(x, y);
	}
}

void CDlite::getSuccnodes(int x, int y)
{
	int dis;

	if ((x + 1) >= 0 && (x + 1)<MAPWIDTH && y >= 0 && y<MAPHEIGHT && !node[x + 1][y].is_in_closetable)
	{
		if (node[x + 1][y].rhs != INT_MAX)
		{
			dis = node[x + 1][y].rhs + c(node[x][y], node[x + 1][y]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x + 1][y]);
			}
		}
	}

	if ((x - 1) >= 0 && (x - 1)<MAPWIDTH && y >= 0 && y<MAPHEIGHT && !node[x - 1][y].is_in_closetable)
	{
		if (node[x - 1][y].rhs != INT_MAX)
		{
			dis = node[x - 1][y].rhs + c(node[x][y], node[x - 1][y]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x - 1][y]);
			}
		}
	}

	if (x >= 0 && x<MAPWIDTH && (y + 1) >= 0 && (y + 1)<MAPHEIGHT && !node[x][y + 1].is_in_closetable)
	{
		if (node[x][y + 1].rhs != INT_MAX)
		{
			dis = node[x][y + 1].rhs + c(node[x][y], node[x][y + 1]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x][y + 1]);
			}
		}
	}

	if (x >= 0 && x<MAPWIDTH && (y - 1) >= 0 && (y - 1)<MAPHEIGHT && !node[x][y - 1].is_in_closetable)
	{
		if (node[x][y - 1].rhs != INT_MAX)
		{
			dis = node[x][y - 1].rhs + c(node[x][y], node[x][y - 1]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x][y - 1]);
			}
		}
	}

	if ((x + 1) >= 0 && (x + 1)<MAPWIDTH && (y + 1) >= 0 && (y + 1)<MAPHEIGHT && !node[x + 1][y + 1].is_in_closetable)
	{
		if (node[x + 1][y + 1].rhs != INT_MAX)
		{
			dis = node[x + 1][y + 1].rhs + c(node[x][y], node[x + 1][y + 1]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x + 1][y + 1]);
			}
		}
	}

	if ((x + 1) >= 0 && (x + 1)<MAPWIDTH && (y - 1) >= 0 && (y - 1)<MAPHEIGHT && !node[x + 1][y - 1].is_in_closetable)
	{
		if (node[x + 1][y - 1].rhs != INT_MAX)
		{
			dis = node[x + 1][y - 1].rhs + c(node[x][y], node[x + 1][y - 1]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x + 1][y - 1]);
			}
		}
	}

	if ((x - 1) >= 0 && (x - 1)<MAPWIDTH && (y + 1) >= 0 && (y + 1)<MAPHEIGHT && !node[x - 1][y + 1].is_in_closetable)
	{
		if (node[x - 1][y + 1].rhs != INT_MAX)
		{
			dis = node[x - 1][y + 1].rhs + c(node[x][y], node[x - 1][y + 1]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x - 1][y + 1]);
			}
		}
	}

	if ((x - 1) >= 0 && (x - 1)<MAPWIDTH && (y - 1) >= 0 && (y - 1)<MAPHEIGHT && !node[x - 1][y - 1].is_in_closetable)
	{
		if (node[x - 1][y - 1].rhs != INT_MAX)
		{
			dis = node[x - 1][y - 1].rhs + c(node[x][y], node[x - 1][y - 1]);
			if (dis < node[x][y].rhs)
			{
				node[x][y].rhs = dis;
				node[x][y].backPointnode = &(node[x - 1][y - 1]);
			}
		}
	}
}

void CDlite::delete_from_opentable(int x, int y)
{
	list<CNode *>::iterator Itor;
	
	for (Itor = openTable.begin(); Itor != openTable.end();)
	{
		if ((*Itor)->x == x && (*Itor)->y == y)
		{
			Itor = openTable.erase(Itor);
		}
		else
		{
			Itor++;
		}
	}

	node[x][y].is_in_opentable = FALSE;
	openNodecount--;
}

int CDlite::c(CNode nd1, CNode nd2)
{
	if (nd1.type == BARRIER || nd2.type == BARRIER)
	{
		return INT_MAX;
	}
	else
	{
		if ((abs(nd1.x - nd2.x) + abs(nd1.y - nd2.y)) == 1)
		{
			return 10;
		}
		else
		{
			return 14;
		}
	}
}

void CDlite::MyFilledCircle(Mat img, Point center, Scalar color)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center,
		3,
		color,
		thickness,
		lineType);
}

void CDlite::showDetails()
{
}

void CDlite::showResult()
{
}

