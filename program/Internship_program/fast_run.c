/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "fast_run.h"
#include "buzzer_driver.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
#define MAX_ROUTE (16)
int g_FastRoute[MAX_ROUTE] =	// 最短走行の経路(直進優先)
{
	Straight, Straight, Straight, Straight	, Right,
	Straight, Straight, Straight, Straight	, Right,
	Straight, Straight, Straight, Right	, Straight,
	GOAL_NOW
};
#define MAX_ROUTE_SHORT (10)
int g_FastRoute2[MAX_ROUTE_SHORT] =	// 最短走行の経路(直進優先)
{
	Straight, Straight	, Straight, Right,
	Right	, Left		, Right	  , Left , 
	Right	, GOAL_NOW
};

/*==============================================================================*/
/*  直進優先最短走行モード		                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void fast_run_straight(void)
{
	accel = SEARCH_ACCEL;
	
	/* まず0.5区画進む */
	straight(STRAIGHT_HALFSECTION,0, SEARCH_SPEED2, SEARCH_SPEED2);	// 0.5区画進む
	
	int route_cnt;
	for(route_cnt = 0; route_cnt < MAX_ROUTE; route_cnt++)
	{
		switch(g_FastRoute[route_cnt])
		{
			case Straight:
				if((route_cnt == 0) || (route_cnt == 5)|| (route_cnt == 10)|| (route_cnt == 14))
				{
					straight(STRAIGHT_SECTION,SEARCH_SPEED2,800,800);	// 1区画進む
				}
				else if((route_cnt == 3) || (route_cnt == 8) || (route_cnt == 12))
				{
					straight(STRAIGHT_SECTION,800,800,SEARCH_SPEED2);	// 1区画進む
				}
				else
				{
					straight(STRAIGHT_SECTION,800,800,800);	// 1区画進む
				}
				break;
			case Right:
				slalom(right,SEARCH_SPEED2);
				break;
			case Left:
				slalom(left,SEARCH_SPEED2);
				break;
			case GOAL_NOW:
				straight(STRAIGHT_SECTION/2,SEARCH_SPEED2,SEARCH_SPEED2,0);
				slalom_enable	= false;
				drv_bz();
				rotate2(right, 200);
				break;
			default:
				break;
		}
	}
	
}

void fast_run(void)
{
	accel = SEARCH_ACCEL;
	
	/* まず0.5区画進む */
	straight(STRAIGHT_HALFSECTION,0, SEARCH_SPEED2, SEARCH_SPEED2);	// 0.5区画進む
	
	int route_cnt;
	for(route_cnt = 0; route_cnt < MAX_ROUTE; route_cnt++)
	{
		switch(g_FastRoute2[route_cnt])
		{
			case Straight:
				if((route_cnt == 0))
				{
					straight(STRAIGHT_SECTION,SEARCH_SPEED2,800,800);	// 1区画進む
				}
				else if((route_cnt == 2))
				{
					straight(STRAIGHT_SECTION,800,800,SEARCH_SPEED2);	// 1区画進む
				}
				else
				{
					straight(STRAIGHT_SECTION,800,800,800);	// 1区画進む
				}
				break;
			case Right:
				slalom(right,SEARCH_SPEED2);
				break;
			case Left:
				slalom(left,SEARCH_SPEED2);
				break;
			case GOAL_NOW:
				straight(STRAIGHT_SECTION,SEARCH_SPEED2,SEARCH_SPEED2,0);
				slalom_enable	= false;
				drv_bz();
				rotate2(right, 200);
				break;
			default:
				break;
		}
	}
	
}