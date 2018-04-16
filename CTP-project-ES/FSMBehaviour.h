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

float target_movement_FSM[] = {

	//end loop		
	S_LOAD,
	PRINT,
	HALT,

	STAT_LOAD, 5,
	STAT_LOAD, 7,
	LT_I32,
	JMPF, 17,
	STAT_LOAD, 3,
	STAT_LOAD, 5,
	ADD_I32,
	STAT_SAVE, 5,

	STAT_LOAD, 6,
	STAT_LOAD, 8,
	LT_I32,
	JMPF, 31,
	STAT_LOAD, 3,
	STAT_LOAD, 6,
	ADD_I32,
	STAT_SAVE, 6,

	STAT_LOAD, 5,
	STAT_LOAD, 7,
	GT_I32,
	JMPF, 45,
	STAT_LOAD, 5,
	STAT_LOAD, 3,
	SUB_I32,
	STAT_SAVE, 5,

	STAT_LOAD, 6,
	STAT_LOAD, 8,
	GT_I32,
	JMPF, 0,
	STAT_LOAD, 6,
	STAT_LOAD, 3,
	SUB_I32,
	STAT_SAVE, 6,
	JMP, 0
};

float random_movement_FSM[]{

	//end loop		
	S_LOAD,
	PRINT,
	HALT,

	STAT_LOAD, 5,
	STAT_LOAD, 7,
	CHECK_NEAR,
	JMPF, 0,

	STAT_LOAD, 6,
	STAT_LOAD, 8,
	CHECK_NEAR,
	JMPF, 0,

	RAND, 770,
	STAT_SAVE, 7,
	RAND, 570,
	STAT_SAVE, 8,
	JMP, 0
};

int counter = 0;

float nearby_food_FSM[]{

	//end loop		
	S_LOAD,
	PRINT,
	HALT,

	CONST_I32, 0,
	GSTORE, counter,

	CLEAR_VEC, 1,

	CHECK_OBJECTS,

	STAT_LOAD, 9,
	CONST_I32, 0,
	GT_I32,
	JMPF, 0,

	CONST_I32, counter,
	GLOAD,
	CHECK_COLOUR, 
	CONST_I32, 1,
	EQ_I32,
	JMPT, 43,

	CONST_I32, counter,
	GLOAD,
	CONST_I32, 1,
	ADD_I32,
	GSTORE, counter,
	CONST_I32, counter,
	GLOAD,
	STAT_LOAD, 9,
	LT_I32,
	JMPF, 0,
	JMP, 17,

	CONST_I32, 1,
	STAT_SAVE, 1,
	CONST_I32, counter,
	GLOAD,
	GET_X_POS,
	STAT_SAVE, 7,
	CONST_I32, counter,
	GLOAD,
	GET_Y_POS,
	STAT_SAVE, 8,

	CONST_I32, counter,
	GLOAD,
	GET_X_POS,
	STAT_LOAD, 5,
	CHECK_NEAR,
	JMPF, 0,
	CONST_I32, counter,
	GLOAD,
	GET_Y_POS,
	STAT_LOAD, 6,
	CHECK_NEAR,
	JMPF, 0,

	CONST_I32, counter,
	GLOAD,
	CHANGE_COLOUR, 0,
	CONST_I32, 25,
	STAT_LOAD, 0,
	ADD_I32,
	STAT_SAVE, 0,
	JMP, 0

};
