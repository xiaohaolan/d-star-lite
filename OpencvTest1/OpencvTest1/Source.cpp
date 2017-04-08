#include <iostream>
#include "Dlite.h"

using namespace std;

#define MAPHEIGHT 1000
#define MAPWIDTH 1000
#define STARTX 960
#define STARTY 710
#define ENDX 950
#define ENDY 700


int main()
{
	CDlite *Dlite = new CDlite(STARTX, STARTY, ENDX, ENDY);
	Dlite->pathPlanning();//起始点终止点坐标
	//Dlite.showResult();
	//Dlite.showDetails();

	waitKey(0);
	delete Dlite;
	return 0;
}