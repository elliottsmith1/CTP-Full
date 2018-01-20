#include <stdio.h> 
#include <stdlib.h>

#include "VirtualM.h"

VM* VirtualM::newVM(int* code, int pc, int datasize)
{      
	// total locals size required to perform a program operations
	VM* vm = (VM*)malloc(sizeof(VM));
	vm->code = code;
	vm->pc = pc;
	vm->fp = 0;
	vm->sp = -1;
	vm->locals = (int*)malloc(sizeof(int) * datasize);
	vm->stack = (int*)malloc(sizeof(int) * stack_size);

	return vm;
}

void VirtualM::delVM(VM* vm) {
	free(vm->locals);
	free(vm->stack);
	free(vm);
}

int VirtualM::GetState()
{
	return state;
}

enum {
	ADD_I32 = 1,    // int add
	SUB_I32 = 2,    // int sub
	MUL_I32 = 3,    // int mul
	LT_I32 = 4,     // int less than
	GT_I32 = 5,		// int greater than
	EQ_I32 = 6,     // int equal
	JMP = 7,        // branch
	JMPT = 8,       // branch if true
	JMPF = 9,       // branch if false
	CONST_I32 = 10,  // push constant integer
	LOAD = 11,      // load from local
	GLOAD = 12,     // load from global
	S_LOAD = 13,	// load state
	S_STORE = 14,	// store state
	STORE = 15,     // store in local
	GSTORE = 16,    // store in global memory
	PRINT = 17,     // print value on top of the stack
	POP = 18,       // throw away top of the stack
	HALT = 19,      // stop program
	CALL = 20,      // call procedure
	RET = 21,      // return from procedure
	PAUSE = 22		// pause program
};

void VirtualM::Run(VM* vm) 
{
	do {
		int opcode = NCODE(vm);        // fetch
		int v, addr, offset, a, b, argc, rval;

		switch (opcode) {   // decode

		case HALT:
			return;  // stop the program

		case CONST_I32:
			v = NCODE(vm);   // get next value from code ...
			PUSH(vm, v);     // ... and move it on top of the stack

			printf("\npushing constant int (%d)\n", v);

			break;

		case ADD_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, a + b);    // ... add those two values and put result on top of the stack

			printf("\nadding %d + %d (%d)\n", a, b, (a + b));

			break;

		case SUB_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, a - b);    // ... subtract those two values and put result on top of the stack

			printf("\nsubtracting %d - %d (%d)\n", a, b, (a - b));

			break;

		case MUL_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, a * b);    // ... multiply those two values and put result on top of the stack

			printf("\nmultiplying %d * %d (%d)\n", a, b, (a*b));

			break;

		case LT_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, (a<b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			printf("\n%d less than %d?", a, b);

			if (a < b)
			{
				printf(" (true)\n");
			}
			else
			{
				printf(" (false)\n");
			}

			break;

		case GT_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, (a>b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			printf("\n%d greater than %d?", a, b);

			if (a > b)
			{
				printf(" (true)\n");
			}
			else
			{
				printf(" (false)\n");
			}

			break;

		case EQ_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, (a == b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			printf("\n%d equal to %d?", a, b);

			if (a == b)
			{
				printf(" (true)\n");
			}
			else
			{
				printf(" (false)\n");
			}

			break;

		case JMP:
			vm->pc = NCODE(vm);  // unconditionaly jump with program counter to provided address

			printf("\jump to opcode instruction: %d\n", NCODE(vm));

			break;

		case JMPT:
			addr = NCODE(vm);  // get address pointer from code ...
			if (POP(vm) == 1)
			{      // ... pop value from top of the stack, and if it's true ...
				vm->pc = addr; // ... jump with program counter to provided address

				printf("\jump true\n opcode: %d\n", addr);
			}

			break;

		case JMPF:
			addr = NCODE(vm);  // get address pointer from code ...
			if (POP(vm) == 0)
			{      // ... pop value from top of the stack, and if it's true ...
				vm->pc = addr; // ... jump with program counter to provided address

				printf("\jump false\n opcode: %d\n", addr);
			}

			break;

		case LOAD:                  // load local value or function arg  
			offset = NCODE(vm);     // get next value from code to identify local variables offset start on the stack
			PUSH(vm, vm->stack[vm->fp + offset]); // ... put on the top of the stack variable stored relatively to frame pointer

			printf("\nlocal load\n");

			break;

		case S_LOAD:                 // load state
			PUSH(vm, state); // ... push current state

			printf("\npushing current state (%d)\n", state);

			break;

		case STORE:                 // store local value or function arg  
			v = POP(vm);            // get value from top of the stack ...
			offset = NCODE(vm);     // ... get the relative pointer address from code ...
			vm->locals[vm->fp + offset] = v;  // ... and store value at address received relatively to frame pointer

			printf("\nstore locally\n");

			break;

		case S_STORE:               // store state
			v = POP(vm);            // get value from top of the stack ...
			state = v;

			printf("\nsaving state (%d)\n", v);

			break;

		case GLOAD:
			addr = POP(vm);             // get pointer address from code ...
			v = vm->locals[addr];         // ... load value from memory of the provided addres ...
			PUSH(vm, v);                // ... and put that value on top of the stack

			printf("\nload global\nvalue: %d\naddress: %d\n", v, addr);

			break;

		case GSTORE:
			v = POP(vm);                // get value from top of the stack ...
			addr = NCODE(vm);           // ... get pointer address from code ...
			vm->locals[addr] = v;         // ... and store value at address received

			printf("\nstore global\nvalue: %d\naddress: %d\n", v, addr);

			break;

		case CALL:
			// we expect all args to be on the stack
			addr = NCODE(vm); // get next instruction as an address of procedure jump ...
			argc = NCODE(vm); // ... and next one as number of arguments to load ...
			PUSH(vm, argc);   // ... save num args ...
			PUSH(vm, vm->fp); // ... save function pointer ...
			PUSH(vm, vm->pc); // ... save instruction pointer ...
			vm->fp = vm->sp;  // ... set new frame pointer ...
			vm->pc = addr;    // ... move instruction pointer to target procedure address

			printf("\nfunction call\n");

			break;

		case RET:
			rval = POP(vm);     // pop return value from top of the stack
			vm->sp = vm->fp;    // ... return from procedure address ...
			vm->pc = POP(vm);   // ... restore instruction pointer ...
			vm->fp = POP(vm);   // ... restore framepointer ...
			argc = POP(vm);     // ... hom many args procedure has ...
			vm->sp -= argc;     // ... discard all of the args left ...
			PUSH(vm, rval);     // ... leave return value on top of the stack

			printf("\nfunction return\n");

			break;

		case POP:
			--vm->sp;      // throw away value at top of the stack

			printf("\nthrowing away top of stack\n");

			break;

		case PRINT:
			v = POP(vm);        // pop value from top of the stack ...
			printf("\nPrinting top of stack: %d\n", v);  // ... and print it					

			break;

		case PAUSE:
			do
			{
				printf("\n\nPaused. Press enter to continue.\n"); // pause until enter is pressed
			} while (getchar() != '\n');

			break;

		default:
			break;
		}

	} while (1);
}

void VirtualM::Machine()
{
	const int state_address = 0;
	int program[] = {

		//start - set state value to 1
		CONST_I32, 1,
		GSTORE, state_address,

		//state 1 - adding to 10
		CONST_I32, 1,
		S_STORE,
		CONST_I32, state_address,
		GLOAD,
		CONST_I32, 1,
		ADD_I32,
		GSTORE, state_address,
		CONST_I32, state_address,
		GLOAD,
		CONST_I32, 10000,
		EQ_I32,
		JMPF, 7,

		//state 2 - adding to 100
		CONST_I32, 2,
		S_STORE,
		CONST_I32, state_address,
		GLOAD,
		CONST_I32, 10,
		ADD_I32,
		GSTORE, state_address,
		CONST_I32, state_address,
		GLOAD,
		CONST_I32, 100000,
		EQ_I32,
		JMPF, 26,

		//restart
		CONST_I32, 1,
		JMP, 0,

		//end loop		
		S_LOAD,
		PRINT,
		//PAUSE,
		HALT

	};

	// initialize virtual machine
	VM* vm = newVM(program,   // program to execute  
		0,    // start address of main function
		1);    // locals to be reserved
	Run(vm);

	//delete vm
	delVM(vm);
}

