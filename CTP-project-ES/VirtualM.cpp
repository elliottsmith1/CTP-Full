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

int VirtualM::GetID()
{
	return machine_id;
}

VM * VirtualM::GetVM()
{
	return vm;
}

void VirtualM::SetID(int _id)
{
	machine_id = _id;
}

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

			printf("\nVM# %d: pushing constant int (%d)\n", machine_id, v);

			break;

		case ADD_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, a + b);    // ... add those two values and put result on top of the stack

			printf("\nVM# %d: adding %d + %d (%d)\n", machine_id, a, b, (a + b));

			break;

		case SUB_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, a - b);    // ... subtract those two values and put result on top of the stack

			printf("\nVM# %d: subtracting %d - %d (%d)\n", machine_id, a, b, (a - b));

			break;

		case MUL_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, a * b);    // ... multiply those two values and put result on top of the stack

			printf("\nVM# %d: multiplying %d * %d (%d)\n", machine_id, a, b, (a*b));

			break;

		case LT_I32:
			b = POP(vm);        // get second value from top of the stack ...
			a = POP(vm);        // ... then get first value from top of the stack ...
			PUSH(vm, (a<b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			printf("\nVM# %d: %d less than %d?", machine_id, a, b);

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

			printf("\nVM# %d: %d greater than %d?", machine_id, a, b);

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

			printf("\nVM# %d: %d equal to %d?", machine_id, a, b);

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

			printf("\nVM# %d: jump to opcode instruction: %d\n", machine_id, NCODE(vm));

			break;

		case JMPT:
			addr = NCODE(vm);  // get address pointer from code ...
			if (POP(vm) == 1)
			{      // ... pop value from top of the stack, and if it's true ...
				vm->pc = addr; // ... jump with program counter to provided address

				printf("\nVM# %d: jump true\nopcode: %d\n", machine_id, addr);
			}

			break;

		case JMPF:
			addr = NCODE(vm);  // get address pointer from code ...
			if (POP(vm) == 0)
			{      // ... pop value from top of the stack, and if it's true ...
				vm->pc = addr; // ... jump with program counter to provided address

				printf("\nVM# %d: jump false\nopcode: %d\n", machine_id, addr);
			}

			break;

		case LOAD:                  // load local value or function arg  
			offset = NCODE(vm);     // get next value from code to identify local variables offset start on the stack
			PUSH(vm, vm->stack[vm->fp + offset]); // ... put on the top of the stack variable stored relatively to frame pointer

			printf("\nVM# %d: local load\n", machine_id);

			break;

		case S_LOAD:                 // load state
			PUSH(vm, state); // ... push current state

			printf("\nVM# %d: pushing current state (%d)\n", machine_id, state);

			break;

		case STORE:                 // store local value or function arg  
			v = POP(vm);            // get value from top of the stack ...
			offset = NCODE(vm);     // ... get the relative pointer address from code ...
			vm->locals[vm->fp + offset] = v;  // ... and store value at address received relatively to frame pointer

			printf("\nVM# %d: store locally\n", machine_id);

			break;

		case S_STORE:               // store state
			v = POP(vm);            // get value from top of the stack ...
			state = v;

			printf("\nVM# %d: saving state (%d)\n", machine_id, v);

			break;

		case GLOAD:
			addr = POP(vm);             // get pointer address from code ...
			v = vm->locals[addr];         // ... load value from memory of the provided addres ...
			PUSH(vm, v);                // ... and put that value on top of the stack

			printf("\nVM# %d: load global\nvalue: %d\naddress: %d\n", machine_id, v, addr);

			break;

		case GSTORE:
			v = POP(vm);                // get value from top of the stack ...
			addr = NCODE(vm);           // ... get pointer address from code ...
			vm->locals[addr] = v;         // ... and store value at address received

			printf("\nVM# %d: store global\nvalue: %d\naddress: %d\n", machine_id, v, addr);

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

			printf("\nVM# %d: function call\n", machine_id);

			break;

		case RET:
			rval = POP(vm);     // pop return value from top of the stack
			vm->sp = vm->fp;    // ... return from procedure address ...
			vm->pc = POP(vm);   // ... restore instruction pointer ...
			vm->fp = POP(vm);   // ... restore framepointer ...
			argc = POP(vm);     // ... hom many args procedure has ...
			vm->sp -= argc;     // ... discard all of the args left ...
			PUSH(vm, rval);     // ... leave return value on top of the stack

			printf("\nVM# %d: function return\n", machine_id);

			break;

		case POP:
			--vm->sp;      // throw away value at top of the stack

			printf("\nVM# %d: throwing away top of stack\n", machine_id);

			break;

		case PRINT:
			v = POP(vm);        // pop value from top of the stack ...
			printf("\nVM# %d: Printing top of stack: %d\n", machine_id, v);  // ... and print it					

			break;

		case PAUSE:
			do
			{
				printf("\n\nVM# %d: Paused. Press enter to continue.\n", machine_id); // pause until enter is pressed
			} while (getchar() != '\n');

			break;

		default:
			break;
		}

	} while (1);
}

void VirtualM::Machine(int* _code)
{
	// initialize virtual machine
	vm = newVM(_code,   // program to execute  
		0,    // start address of main function
		1);    // locals to be reserved
	
	Run(vm);
}

