#include "VirtualM.h"

float hunger_FSM[] = {

	//end loop		
	S_LOAD,
	PRINT,
	HALT,

	//check if food is above 1
	//if so, deduct some
	//otherwise jump to state 4
	STAT_LOAD, 0,
	CONST_I32, 1,
	GT_I32,
	JMPF, 73,
	STAT_LOAD, 0,
	CONST_I32, 0.01f,
	SUB_I32,
	STAT_SAVE, 0,

	//state 0 
	//check if food is above 90
	//set speed to not moving
	CONST_I32, 0,
	S_STORE,
	CONST_I32, 0,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 90,	
	GT_I32,
	JMPT, 0,

	//state 1
	//check if food is above 50
	//set speed to 1
	CONST_I32, 1,
	S_STORE,
	CONST_I32, 1,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 50,	
	GT_I32,
	JMPT, 0,

	//set state to 2
	//check if food is above 25
	//set speed to 1.5
	CONST_I32, 2,
	S_STORE,
	CONST_I32, 1.5,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 25,	
	GT_I32,
	JMPT, 0,

	//set state to 3
	//check if food is above 10
	//set speed to 2
	CONST_I32, 3,
	S_STORE,
	CONST_I32, 2,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 10,
	GT_I32,
	JMPT, 0,

	//set state to 4
	//check if food is above 1
	//if not == starving 
	//set speed to 0.5
	//deduct health
	STAT_LOAD, 0,
	CONST_I32, 1,
	LT_I32,
	JMPF, 0,
	CONST_I32, 4,
	S_STORE,	
	CONST_I32, 0.5f,
	STAT_SAVE, 3,
	STAT_LOAD, 4,
	CONST_I32, 1,
	GT_I32,
	JMPF, 0,
	STAT_LOAD, 4,
	CONST_I32, 0.03f,
	SUB_I32,
	STAT_SAVE, 4,
	JMP, 0
};

float aquire_food_FSM[] = {

	//end loop		
	S_LOAD,
	PRINT,
	HALT,

	//if food in sight, set to state 1
	//state 0 

	CONST_I32, 0,
	S_STORE,
	STAT_LOAD, 1,
	CONST_I32, 0,
	EQ_I32,
	JMPT, 0,

	//state 1

	CONST_I32, 1,
	S_STORE,
	JMP, 0
};
