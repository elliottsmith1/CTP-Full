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
	//set speed 
	CONST_I32, 0,
	S_STORE,
	CONST_I32, 0.2,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 90,	
	GT_I32,
	JMPT, 0,

	//state 1
	//check if food is above 50
	//set speed 
	CONST_I32, 1,
	S_STORE,
	CONST_I32, 0.4,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 50,	
	GT_I32,
	JMPT, 0,

	//set state to 2
	//check if food is above 25
	//set speed 
	CONST_I32, 2,
	S_STORE,
	CONST_I32, 0.6,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 25,	
	GT_I32,
	JMPT, 0,

	//set state to 3
	//check if food is above 10
	//set speed
	CONST_I32, 3,
	S_STORE,
	CONST_I32, 0.8,
	STAT_SAVE, 3,
	STAT_LOAD, 0,
	CONST_I32, 10,
	GT_I32,
	JMPT, 0,

	//set state to 4
	//check if food is above 1
	//if not == starving 
	//set speed 
	//deduct health
	STAT_LOAD, 0,
	CONST_I32, 1,
	LT_I32,
	JMPF, 0,
	CONST_I32, 4,
	S_STORE,	
	CONST_I32, 0.1f,
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

	STAT_LOAD, 9, //7
	CONST_I32, 0,
	GT_I32,
	JMPF, 0,

	CONST_I32, counter, //14
	GLOAD,
	CHECK_COLOUR, 
	CONST_I32, 1,
	EQ_I32,
	JMPT, 41,

	CONST_I32, counter, //23
	GLOAD,
	CONST_I32, 1,
	ADD_I32,
	GSTORE, counter,
	CONST_I32, counter,
	GLOAD,
	STAT_LOAD, 9,
	LT_I32,
	JMPF, 0,
	JMP, 14,

	CONST_I32, 1, //41
	STAT_SAVE, 1,
	CONST_I32, counter,
	GLOAD,
	GET_X_POS,
	STAT_SAVE, 7,
	CONST_I32, counter,
	GLOAD,
	GET_Y_POS,
	STAT_SAVE, 8,

	CONST_I32, counter, //57
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

	CONST_I32, counter, //74
	GLOAD,
	CHANGE_COLOUR, 0,
	CONST_I32, 25,
	STAT_LOAD, 0,
	ADD_I32,
	STAT_SAVE, 0,
	JMP, 0

};

int t_counter = 0;

float thirst_FSM[] = {

	//end loop		
	S_LOAD,
	PRINT,
	HALT,

	CONST_I32, 0,
	GSTORE, t_counter,

	STAT_LOAD, 12,	//7
	CONST_I32, 1,
	GT_I32,
	JMPF, 0,
	STAT_LOAD, 12,
	CONST_I32, 0.01f,
	SUB_I32,
	STAT_SAVE, 12,

	STAT_LOAD, 12,	//21
	CONST_I32, 35,
	LT_I32,
	JMPF, 32,
	CONST_I32, 1,
	STAT_SAVE, 13,

	STAT_LOAD, 13,	//32
	CONST_I32, 1,
	EQ_I32,
	JMPF, 0,

	STAT_LOAD, 9, //39
	CONST_I32, 0,
	GT_I32,
	JMPF, 0,

	CONST_I32, t_counter, //46
	GLOAD,
	CHECK_COLOUR,
	CONST_I32, 3,
	EQ_I32,
	JMPT, 73,

	CONST_I32, t_counter, //55
	GLOAD,
	CONST_I32, 1,
	ADD_I32,
	GSTORE, t_counter,
	CONST_I32, t_counter,
	GLOAD,
	STAT_LOAD, 9,
	LT_I32,
	JMPF, 0,
	JMP, 46,

	CONST_I32, t_counter,	//73
	GLOAD,
	GET_X_POS,
	STAT_SAVE, 7,
	CONST_I32, t_counter,
	GLOAD,
	GET_Y_POS,
	STAT_SAVE, 8,

	CONST_I32, t_counter, //85
	GLOAD,
	GET_X_POS,
	STAT_LOAD, 5,
	CHECK_NEAR,
	JMPF, 0,
	CONST_I32, t_counter,
	GLOAD,
	GET_Y_POS,
	STAT_LOAD, 6,
	CHECK_NEAR,
	JMPF, 0,

	CONST_I32, 0.2,	//103
	STAT_LOAD, 12,
	ADD_I32,
	STAT_SAVE, 12,
	STAT_LOAD, 12,
	CONST_I32, 90,
	GT_I32,
	JMPF, 0,
	CONST_I32, 0,
	STAT_SAVE, 13,
	JMP, 0
};
