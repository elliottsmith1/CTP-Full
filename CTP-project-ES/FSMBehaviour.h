#include "VirtualM.h"

//address of counting int
const int counting_address = 0;

int counting_FSM[] = {

	//start - set count value to 1
	CONST_I32, 1,
	GSTORE, counting_address,

	//state 1 - adding by 1

	//set state to 1
	CONST_I32, 1,
	S_STORE,
	//get count
	CONST_I32, counting_address,
	GLOAD,
	//add 1 to count
	CONST_I32, 1,
	ADD_I32,
	//store result
	GSTORE, counting_address,
	//load count
	CONST_I32, counting_address,
	GLOAD,
	//check if equal to max
	CONST_I32, 5000,
	EQ_I32,
	//if not yet reached then back to start
	JMPF, 7,

	//state 2 - adding by 10
	//set state to 2
	CONST_I32, 2,
	S_STORE,
	//get count
	CONST_I32, counting_address,
	GLOAD,
	//add 10
	CONST_I32, 1,
	ADD_I32,
	//store count
	GSTORE, counting_address,
	//load count
	CONST_I32, counting_address,
	GLOAD,
	//check if equal to max
	CONST_I32, 10000,
	EQ_I32,
	//keep going until reached
	JMPF, 26,

	//restart back at beggining 
	CONST_I32, 1,
	JMP, 0,

	//end loop		
	S_LOAD,
	PRINT,
	PAUSE,
	HALT
}; 

int counting_FSM2[] = {

	//start - set count value to 1
	CONST_I32, 1,
	GSTORE, counting_address,

	//state 1 - adding by 1

	//set state to 1
	CONST_I32, 1,
	S_STORE,
	//get count
	CONST_I32, counting_address,
	GLOAD,
	//add 1 to count
	CONST_I32, 1,
	ADD_I32,
	//store result
	GSTORE, counting_address,
	//load count
	CONST_I32, counting_address,
	GLOAD,
	//check if equal to max
	CONST_I32, 3000,
	EQ_I32,
	//if not yet reached then back to start
	JMPF, 7,

	//state 2 - adding by 1
	//set state to 2
	CONST_I32, 2,
	S_STORE,
	//get count
	CONST_I32, counting_address,
	GLOAD,
	//add 10
	CONST_I32, 1,
	ADD_I32,
	//store count
	GSTORE, counting_address,
	//load count
	CONST_I32, counting_address,
	GLOAD,
	//check if equal to max
	CONST_I32, 6000,
	EQ_I32,
	//keep going until reached
	JMPF, 26,

	//state 3 - adding by 1
	//set state to 2
	CONST_I32, 3,
	S_STORE,
	//get count
	CONST_I32, counting_address,
	GLOAD,
	//add 10
	CONST_I32, 1,
	ADD_I32,
	//store count
	GSTORE, counting_address,
	//load count
	CONST_I32, counting_address,
	GLOAD,
	//check if equal to max
	CONST_I32, 9000,
	EQ_I32,
	//keep going until reached
	JMPF, 45,

	//restart back at beggining 
	CONST_I32, 1,
	JMP, 0,

	//end loop		
	S_LOAD,
	PRINT,
	PAUSE,
	HALT
};
