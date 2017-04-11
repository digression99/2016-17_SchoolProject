#include "MainTetris.h"

int dataMap[MAP_NUM][MAP_HEIGHT][MAP_WIDTH] =
{
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1,
	1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1,
	1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
	1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
	1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

PlayTetris::PlayTetris()
{	genDefaultBlock();		
	this->setMergeMap(1);
	this->makeBitMap();

	this->isOver = false;
	this->isMerged = false;
	this->isFirst = true;
	this->keyFree = true;
	this->isShifted = false;
	this->itemArrIdx = 0;
}

void PlayTetris::rotateBlock()
{
	this->eraseBlock();
	this->movingBlock.rotate();
	this->mergeBlock();
}

void PlayTetris::leftBlock()
{
	this->eraseBlock();
	this->movingBlock.setAbsp(
		this->movingBlock.getAbsp()->getX() - 2,
		this->movingBlock.getAbsp()->getY());
	this->mergeBlock();
}
void PlayTetris::rightBlock()
{
	this->eraseBlock();
	this->movingBlock.setAbsp(
		this->movingBlock.getAbsp()->getX() + 2,
		this->movingBlock.getAbsp()->getY());
	this->mergeBlock();
}

bool PlayTetris::rotationCheck()
{
	this->eraseBlock();
	Block cb = this->movingBlock;
	cb.rotate();

	int x = (cb.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = cb.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표

	bool check = false;

	for (int i = 0; i < 3; i++)
	{
		if (this->mergeMap[y + cb.getBp()[i].getY() - 2][x + cb.getBp()[i].getX() - 2].getData() == BLOCK_WALL)
		{
			check = true;
			break;
		}
	}

	if (this->mergeMap[y][x].getData() == BLOCK_WALL)
	{
		check = true;
	}
	this->mergeBlock();
	return check;
}

void PlayTetris::startBlock()
{
	nextBlock.erase();

	swapBlock(&this->nextBlock, &this->movingBlock);
	movingBlock.setAbsp(MAP_LEFT + (MAP_WIDTH / 2), MAP_TOP - 1);

	setNextBlock();
	this->nextBlock.print();
	this->mergeBlock();
}

void PlayTetris::shiftBlock()
{
}

void PlayTetris::unShiftBlock()
{
}

void PlayTetris::swapBlock(Block * b1, Block * b2)
{
	Block temp = *b1;
	*b1 = *b2;
	*b2 = temp;
}
void PlayTetris::makeBitMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		bitMap[i] = 0;
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (this->mergeMap[i][j].getData() == 0)
			{
				continue;
			}
			else
			{
				unsigned short shiftNum = ((unsigned)0x8000) >> j;

				bitMap[i] |= shiftNum;
			}
		}
	}
}

void PlayTetris::genDefaultBlock(){
	int xAr[] = {
		2, 2, 2, // stick
		1, 1, 2, // left mini
		2, 3, 3, // right mini
		2, 2, 3, // right big
		1, 2, 2, // left big
		1, 1, 2, // square
		1, 2, 3, // cross
	};
	int yAr[] = {
		1, 3, 4, // stick
		2, 3, 1, // left mini
		1, 2, 3, // right mini
		1, 3, 3, // right big
		3, 1, 3, // left big
		2, 3, 3, // square
		2, 3, 2, // cross
	};

	for (int i = 0; i < 7; i++)
	{
		BlockPointer bp1(xAr[3 * i], yAr[3 * i], i + 1, BLOCK_WALL);
		BlockPointer bp2(xAr[3 * i + 1], yAr[3 * i + 1], i + 1, BLOCK_WALL);
		BlockPointer bp3(xAr[3 * i + 2], yAr[3 * i + 2], i + 1, BLOCK_WALL);
		BlockPointer bp4(MAP_LEFT + MAP_WIDTH + 15, MAP_TOP, i + 1, BLOCK_WALL);
		Block lb(bp1, bp2, bp3, bp4, i + 1);
		bArr[i] = lb;
	}
}

void PlayTetris::setNextBlock()
{	
	this->nextBlock = getRandBlock(); //new Bock(b[rand()%7]);	// Block 기본 꼴 모음에서 랜덤으로 nextBlock에 랜덤으로 저장
	if(rand() % 10 == 0)
	{
      int i = rand() % 3;
	  int j = rand() % 2;

	  if (j == 0)
	  {
		  this->nextBlock.getBp()[i].setData(BLOCK_ITEM1);
		  this->nextBlock.getBp()[i].setColor(YELLOW);
	  }
	  else if (j == 1)
	  {
		  this->nextBlock.getBp()[i].setData(BLOCK_ITEM2);
		  this->nextBlock.getBp()[i].setColor(LIGHTMAGENTA);
	  }
   }
}	//생성된 랜덤 블록 객체 nextBlock 에 저장

Block PlayTetris::getRandBlock()
{ //랜덤으로 블록 기본 모형 리턴
	int i = rand() % 7;
	Block randBlock;
	randBlock = bArr[rand() % 7];
	return randBlock;
}

bool PlayTetris::checkBlock()
{ // check the bottom of the block
	int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표
	bool check = false;

	this->eraseBlock();

	for (int i = 0; i < 3; i++)
	{
		if (this->mergeMap[
			y + this->movingBlock.getBp()[i].getY() - 2 + 1][
			x + this->movingBlock.getBp()[i].getX() - 2].getData() == BLOCK_WALL)
		{
			check = true;
			break;
		}
	}

	if (this->mergeMap[y + 1][x].getData() == BLOCK_WALL)
	{
		check = true;
	}

	this->mergeBlock();

	if (check)
	{
		this->isMerged = true;
	}

	return check;
}//블록이 닿아는지 체크  닿으면 true 안닿으면 false

bool PlayTetris::mergeBlock()
{
   int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
   int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표

   for (int i = 0; i < 3; i++)
   {
      int dx = x + this->movingBlock.getBp()[i].getX() - 2;
      int dy = y + this->movingBlock.getBp()[i].getY() - 2;

	  this->mergeMap[dy][dx].setColor(
		  this->movingBlock.getBp()[i].getColor());
	  this->mergeMap[dy][dx].setData(
		  this->movingBlock.getBp()[i].getData());
   }
   this->mergeMap[y][x].setColor(
	   this->movingBlock.getColor());
   this->mergeMap[y][x].setData(BLOCK_WALL);
   
   bool comboOnGoing = this->checkLine();
   this->makeBitMap();
   return comboOnGoing;
}

bool PlayTetris::checkLine()
{ // fixed
	int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표
	bool check = false;
	bool check2 = false;
	bool check3 = false;
	int yArr[4];
	int lineNum = 0;

	int delLineY[4];
	int delLineIdx = 0;
	BlockPointer itemBp[20];
	BlockPointer bp(0, 0, BLACK, BLOCK_VOID);
	int itemBpIdx = 0;

	if (!this->isMerged)
	{
		return false;
	}

	////data setting
	for (int i = MAP_HEIGHT - 2; i >= 0 ; i--)
	{
		if ((this->bitMap[i] & 0xFFFF) == 0xFFFF)
		{
			for (int j = 1; j < MAP_WIDTH - 1; j++)
			{
				if (this->mergeMap[i][j].getData() > 1)
				{
					itemBp[itemBpIdx] = this->mergeMap[i][j];
					itemBpIdx++;
				}
			}
			delLineY[delLineIdx] = i;
			delLineIdx++;
		}
	}

	if (delLineIdx == 0) 
	{
		return false;
	}

	for (int i = 0; i < itemBpIdx; i++)
	{ // item used.
		itemEffect(itemBp[i].getX(),
			itemBp[i].getY(),
			itemBp[i].getData());
	}

	for (int i = 0; i < delLineIdx; i++)
	{
		for (int j = 1; j < MAP_WIDTH - 1; j++)
		{
			bp.setX(j);
			bp.setY(delLineY[i]);
			this->mergeMap[delLineY[i]][j] = bp;
		}
	}

	for (int i = 0; i < delLineIdx; i++)
	{
		for (int k = delLineY[i] + i; k > 1; k--)
		{
			for (int j = 1; j < MAP_WIDTH - 1; j++)
			{
				this->mergeMap[k][j].setColor(
					this->mergeMap[k - 1][j].getColor());
				this->mergeMap[k][j].setData(
					this->mergeMap[k - 1][j].getData());
				//this->mergeMap[k][j] = this->mergeMap[k - 1][j];
			}
		}
		g.addScore(g.getCombo() * g.getLevel() * 10);
		//delLineY[i] += (i + 1);
	}
	return true;
}

void PlayTetris::itemEffect(int x, int y, int data)
{ // fixed
	BlockPointer bp(0, 0, BLACK, 0);
	BlockPointer iArr[20];
	int iArrIdx = 0;
	switch (data)
	{
	case 2:
		for (int i = 0; i < MAP_HEIGHT - 1; i++)
		{
			if (y != i)
			{
				if (this->mergeMap[i][x].getData() > 1)
				{ // find data.
					iArr[iArrIdx].setData(
						this->mergeMap[i][x].getData());
					iArr[iArrIdx].setX(x);//this->mergeMap[i][x].getX());
					iArr[iArrIdx].setY(i);//this->mergeMap[i][x].getY());
					iArrIdx++;
				}
			}
			bp.setX(x);
			bp.setY(i);
			this->mergeMap[i][x] = bp;
			g.addScore(10*g.getLevel());
		}
		break;
	case 3:
		for (int i = y - 2; i <= y + 2; i++)
		{
			if (i < 0)// || i > 19)
			{
				continue;
			}
			else if (i > 19) 
			{
				break;
			}

			for (int j = x - 2; j <= x + 2; j++)
			{
				if (j < 1)
				{
					continue;
				}
				else if (j > 14)
				{
					break;
				}

				if ((y != i) && (x != j))
				{
					if (this->mergeMap[i][j].getData() > 1)
					{
						iArr[iArrIdx].setData(
							this->mergeMap[i][j].getData());
						iArr[iArrIdx].setX(j);
						iArr[iArrIdx].setY(i);
						iArrIdx++;
					}
				}
				bp.setX(j);
				bp.setY(i);
				this->mergeMap[i][j] = bp;
				g.addScore(10*g.getLevel());
			}
		}
		break;
	}

	for (int i = 0; i < iArrIdx; i++)
	{// use all the item.
		itemEffect(iArr[i].getX(),iArr[i].getY(), iArr[i].getData());
	}
}

bool PlayTetris::checkWall()
{
	this->eraseBlock();
	int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표
	bool check = false;

	for (int i = 0; i < 3; i++)
	{
		if (this->mergeMap[y + this->movingBlock.getBp()[i].getY() - 2][x + this->movingBlock.getBp()[i].getX() - 2 + 1].getData() == 1)
		{
			check = true;
			break;
		}
		else if (this->mergeMap[y + this->movingBlock.getBp()[i].getY() - 2][x + this->movingBlock.getBp()[i].getX() - 2 - 1].getData() == 1)
		{
			check = true;
			break;
		}
	}

	if (this->mergeMap[y][x + 1].getData() == 1)
	{
		check = true;
	}
	else if (this->mergeMap[y][x - 1].getData() == 1)
	{
		check = true;
	}
	this->mergeBlock();
	return check;
}

void PlayTetris::setMergeMap(int mn)
{ // fixed
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			this->mergeMap[i][j].setX(j);
			this->mergeMap[i][j].setY(i);
			this->mergeMap[i][j].setData(dataMap[mn][i][j]);
			if (dataMap[mn][i][j] == 0)
			{
				this->mergeMap[i][j].setColor(BLACK);
			}
			else
			{
				this->mergeMap[i][j].setColor(DARKGRAY);
			}
			if (j == 0 || j == (MAP_WIDTH - 1) || i == MAP_HEIGHT - 1)
			{
				this->mergeMap[i][j].setColor(
					this->g.getMapColor());
			}
		}
	}
}

void PlayTetris::showMergeMap()
{
	int i, j;
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			textColor(
				this->mergeMap[i][j].getColor(), BLACK);
			gotoxy(
				this->mergeMap[i][j].getX() * 2 + MAP_LEFT,
				this->mergeMap[i][j].getY() + MAP_TOP);
			printf("■");
		}
	}
	textColor(DARKGRAY, BLACK);
	return;
}

bool PlayTetris::checkLeftWall()
{
	this->eraseBlock();
	int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT   + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표
	bool check = false;

	for (int i = 0; i < 3; i++)
	{
		if (this->mergeMap[y + this->movingBlock.getBp()[i].getY() - 2][x + this->movingBlock.getBp()[i].getX() - 2 - 1].getData() == 1)
		{
			check = true;
			break;
		}
	}

	if (this->mergeMap[y][x - 1].getData() == 1)
	{
		check = true;
	}
	this->mergeBlock();

	return check;
}
bool PlayTetris::checkRightWall()
{
	this->eraseBlock();
	int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표
	bool check = false;

	for (int i = 0; i < 3; i++)
	{
		if (this->mergeMap[y + this->movingBlock.getBp()[i].getY() - 2][x + this->movingBlock.getBp()[i].getX() - 2 + 1].getData() == 1)
		{
			check = true;
			break;
		}
	}

	if (this->mergeMap[y][x + 1].getData() == 1)
	{
		check = true;
	}
	this->mergeBlock();

	return check;
}

void PlayTetris::downBlock()
{
	this->eraseBlock();
	this->movingBlock.getAbsp()->setY(
		this->movingBlock.getAbsp()->getY() + 1);
	this->mergeBlock();
}

void PlayTetris::deletePixel()
{

}

void PlayTetris::compressPixel()
{
}

void PlayTetris::eraseBlock()
{
	int x = (this->movingBlock.getAbsp()->getX() - MAP_LEFT + 4) / 2; // center 의 배열 인덱스 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2 - MAP_TOP; // center 의 배열 인덱스 y 좌표
	for (int i = 0; i < 3; i++)
	{
		int dx = x + this->movingBlock.getBp()[i].getX() - 2;
		int dy = y + this->movingBlock.getBp()[i].getY() - 2;

		this->mergeMap[dy][dx].setData(BLOCK_VOID);// = 0;
		this->mergeMap[dy][dx].setColor(BLACK);
	}
	this->mergeMap[y][x].setData(BLOCK_VOID);// = 0;
	this->mergeMap[y][x].setColor(BLACK);
}//블록 지움

void PlayTetris::showBlock()
{ // problem
	int x = this->movingBlock.getAbsp()->getX() + 4; // center 의 절대 x 좌표
	int y = this->movingBlock.getAbsp()->getY() + 2; // center 의 절대 y 좌표

	gotoxy(x, y);
	cout << "■";

	for (int i = 0; i < 3; i++)
	{
		gotoxy(x + 2 * (this->movingBlock.getBp()[i].getX() - 2), y + this->movingBlock.getBp()[i].getY() - 2);
		cout << "■";
	}
}

void PlayTetris::showNextBlock()
{
}// 다음 블록을 보여줌
void PlayTetris::showShiftBlock()
{
}// shift된 블록을 보여줌

//블록 객체 만들고 cp 를 받아서 도형을 보여줌
//사용자가 키보드를 입력 안하면 블록이 걸리는지 checking - > move 

void PlayTetris::printBitMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		gotoxy(70, i + 1);
		printf("%x\n", bitMap[i]);
	}
}

void PlayTetris::showTetrisMap(int select)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			gotoxy(36 + j * 2, 2 + i);
			switch (dataMap[select][i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("■");
				break;
			}
		}
	}
}