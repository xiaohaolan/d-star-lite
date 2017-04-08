#pragma once
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <limits.h>
#include <afxwin.h> //类的序列化
#include <list>
#include "Node.h"
#include "Cmpare.h"

using namespace std;
using namespace cv;


#define MAPHEIGHT 1000
#define MAPWIDTH 1000
#define MAPSIZE 1000000
#define VACANT 0
#define BARRIER 1
#define STARTNODE 2
#define ENDNODE 3

#define REGIONLENGTH 10

#define INITWIDTH 50


class CDlite
{
public:
	CNode nd1;
	CNode node[MAPHEIGHT][MAPWIDTH];

	std::list<CNode *> openTable;

	int openNodecount = 0;
	int closeNodecount = 0;

	int start_x;
	int start_y;
	int end_x;
	int end_y;

	Mat atom_image = Mat::zeros(MAPWIDTH, MAPHEIGHT, CV_8UC3);

	CNode *startNode;
	CNode *endNode;
	CNode *currNode;

	CDlite(void);
	CDlite(int startx, int starty, int endx, int endy);
	~CDlite();

	void pathPlanning();
	void showDetails();
	void showResult();

	void nodeSerialization();
	void nodeDeSerialization();

	int readMap();	//读取地图文件
	void roadInit();
	void mapInit();
	void insert_to_opentable(int x, int y);
	void delete_from_opentable(int x, int y);

	void updateVertex(int x, int y);
	void getPrednodes(int x, int y);
	void getSuccnodes(int x, int y);
	int CalculateKey(CNode * node);
	int c(CNode nd1, CNode nd2);//两点距离

	//画图函数
	void drawWindow();
	void showWindow();
	void MyFilledCircle(Mat img, Point center, Scalar color);
};

