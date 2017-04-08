#include <iostream>
#include "Dlite.h"

using namespace std;

#define MAPHEIGHT 1000
#define MAPWIDTH 1000
#define STARTX 530
#define STARTY 530
#define ENDX 500
#define ENDY 500

int CDlite::start_x = STARTX;
int CDlite::start_y = STARTY;
int CDlite::end_x = ENDX;
int CDlite::end_y = ENDY;

int main()
{

	CDlite *Dlite = new CDlite();
	Dlite->pathPlanning();//起始点终止点坐标
	//Dlite.showResult();
	//Dlite.showDetails();

	waitKey(0);
	delete Dlite;
	return 0;
}