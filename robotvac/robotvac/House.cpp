#include "House.h"
#include "SimulationPrintUtils.h"

House::House(char _shortName[], char _longName[], int len, int wid, char ** house)
{
	length = len;
	width = wid;
	strcpy(shortName, _shortName);
	strcpy(longName, _longName);
	curHouse = new char*[wid];

	// Init copy of house
	for (int i = 0; i < wid; i++)
	{
		curHouse[i] = new char[len];
		strcpy(curHouse[i], house[i]);
	}

	repairHouse();
}


SensorInformation House::Sense(Point location)
{
	SensorInformation info;

	// Check if there is wall North
	if (this->curHouse[location.getX()][location.getY() - 1] == 'W')
		info.isWall[WallInfo::North] = true;

	// South
	if (this->curHouse[location.getX()][location.getY() + 1] == 'W')
		info.isWall[WallInfo::South] = true;

	// East
	if (this->curHouse[location.getX() + 1][location.getY()] == 'W')
		info.isWall[WallInfo::East] = true;

	// West
	if (this->curHouse[location.getX() - 1][location.getY()] == 'W')
		info.isWall[WallInfo::West] = true;

	info.dirtLevel = curHouse[location.getX()][location.getY()];

	return info;
}

bool House::Clean(Point p)
{
	char dirt = curHouse[p.getX()][p.getY()]--;
	return ((dirt - '0' > 0 && dirt - '0' <= 9));

}

void House::repairHouse()
{
	// put walls on Sides
	for (int i = 0; i < this->width; i++)
	{
		this->curHouse[i][0] = 'W';
		this->curHouse[i][this->length - 1] = 'W';
	}
		
	// put Walls on Top & Bot
	for (int i = 0; i < this->length; i++)
	{
		this->curHouse[0][i] = 'W';
		this->curHouse[this->width - 1][i] = 'W';
	}
}

bool House::isHouseClean()
{
	// Check on every block
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->length; j++)
		{
			if (this->curHouse[i][j]-'0' > 0 && this->curHouse[i][j]-'0' <= 9)
				return false;
		}
	}

	return true;
}

Point House::findDockingStation()
 {
	for (size_t row = 0; row < length; ++row) {
		for (size_t col = 0; col < width; ++col) {
			if (curHouse[row][col] == House::DOCKING) {
				return Point(col, row); 
			}
		}
	}
	return Point(-1, -1);
}

void House::printDiscoveredPoints(Point& point)
{
	SimulationPrintUtils::printPointOnMovedHouse(curHouse, length, width, point, findDockingStation(), false, '@');
	SimulationPrintUtils::printPointOnMovedHouse(curHouse, length, width, point.GetDownPoint(),
		findDockingStation(), true, '#');
	SimulationPrintUtils::printPointOnMovedHouse(curHouse, length, width, point.GetLeftPoint(),
		findDockingStation(), true, '#');
	SimulationPrintUtils::printPointOnMovedHouse(curHouse, length, width, point.GetRightPoint(),
		findDockingStation(), true, '#');
	SimulationPrintUtils::printPointOnMovedHouse(curHouse, length, width, point.GetUpperPoint(),
		findDockingStation(), true, '#');
}