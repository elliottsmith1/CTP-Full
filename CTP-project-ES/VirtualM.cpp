#include "VirtualM.h"

VM* VirtualM::newVM(int* _code, int _pc, int _datasize)
{      
	// total locals size required to perform a program operations
	vm = (VM*)malloc(sizeof(VM));
	vm->code = _code;
	vm->pc = _pc;
	vm->fp = 0;
	vm->sp = -1;
	vm->locals = (int*)malloc(sizeof(int) * _datasize);
	vm->stack = (int*)malloc(sizeof(int) * stack_size);

	return vm;
}

void VirtualM::delVM(VM* _vm) {
	free(_vm->locals);
	free(_vm->stack);
	free(_vm);
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

void VirtualM::SetStats(EntityStats* _stats)
{
	stats = _stats;
}

void VirtualM::SetID(int _id)
{
	machine_id = _id;
}

void VirtualM::Run(VM* _vm) 
{
	vm->pc = 0;

	do {
		int opcode = NCODE(_vm);        // fetch
		int v, addr, offset, a, b, argc, rval;

		switch (opcode) {   // decode

		case HALT:
			return;  // stop the program

		case CONST_I32:
			v = NCODE(_vm);   // get next value from code ...
			PUSH(_vm, v);     // ... and move it on top of the stack

			printf("\nVM# %d: pushing constant int (%d)\n", machine_id, v);

			break;

		case ADD_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, a + b);    // ... add those two values and put result on top of the stack

			printf("\nVM# %d: adding %d + %d (%d)\n", machine_id, a, b, (a + b));

			break;

		case SUB_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, a - b);    // ... subtract those two values and put result on top of the stack

			printf("\nVM# %d: subtracting %d - %d (%d)\n", machine_id, a, b, (a - b));

			break;

		case MUL_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, a * b);    // ... multiply those two values and put result on top of the stack

			printf("\nVM# %d: multiplying %d * %d (%d)\n", machine_id, a, b, (a*b));

			break;

		case LT_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, (a<b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

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
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, (a>b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

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
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, (a == b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

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
			_vm->pc = NCODE(_vm);  // unconditionaly jump with program counter to provided address

			printf("\nVM# %d: jump to opcode instruction: %d\n", machine_id, NCODE(vm));

			break;

		case JMPT:
			addr = NCODE(_vm);  // get address pointer from code ...
			if (POP(_vm) == 1)
			{      // ... pop value from top of the stack, and if it's true ...
				_vm->pc = addr; // ... jump with program counter to provided address

				printf("\nVM# %d: jump true\nopcode: %d\n", machine_id, addr);
			}

			break;

		case JMPF:
			addr = NCODE(_vm);  // get address pointer from code ...
			if (POP(_vm) == 0)
			{      // ... pop value from top of the stack, and if it's true ...
				_vm->pc = addr; // ... jump with program counter to provided address

				printf("\nVM# %d: jump false\nopcode: %d\n", machine_id, addr);
			}

			break;

		case LOAD:                  // load local value or function arg  
			offset = NCODE(_vm);     // get next value from code to identify local variables offset start on the stack
			PUSH(_vm, _vm->stack[_vm->fp + offset]); // ... put on the top of the stack variable stored relatively to frame pointer

			printf("\nVM# %d: local load\n", machine_id);

			break;

		case S_LOAD:                 // load state
			PUSH(_vm, state); // ... push current state

			printf("\nVM# %d: pushing current state (%d)\n", machine_id, state);

			break;

		case STORE:                 // store local value or function arg  
			v = POP(_vm);            // get value from top of the stack ...
			offset = NCODE(_vm);     // ... get the relative pointer address from code ...
			_vm->locals[_vm->fp + offset] = v;  // ... and store value at address received relatively to frame pointer

			printf("\nVM# %d: store locally\n", machine_id);

			break;

		case S_STORE:               // store state
			v = POP(_vm);            // get value from top of the stack ...
			state = v;

			printf("\nVM# %d: saving state (%d)\n", machine_id, v);

			break;

		case GLOAD:
			addr = POP(_vm);             // get pointer address from code ...
			v = _vm->locals[addr];         // ... load value from memory of the provided addres ...
			PUSH(_vm, v);                // ... and put that value on top of the stack

			printf("\nVM# %d: load global\nvalue: %d\naddress: %d\n", machine_id, v, addr);

			break;

		case GSTORE:
			v = POP(_vm);                // get value from top of the stack ...
			addr = NCODE(_vm);           // ... get pointer address from code ...
			_vm->locals[addr] = v;         // ... and store value at address received

			printf("\nVM# %d: store global\nvalue: %d\naddress: %d\n", machine_id, v, addr);

			break;

		case CALL:
			// we expect all args to be on the stack
			addr = NCODE(_vm); // get next instruction as an address of procedure jump ...
			argc = NCODE(_vm); // ... and next one as number of arguments to load ...
			PUSH(_vm, argc);   // ... save num args ...
			PUSH(_vm, _vm->fp); // ... save function pointer ...
			PUSH(_vm, _vm->pc); // ... save instruction pointer ...
			_vm->fp = _vm->sp;  // ... set new frame pointer ...
			_vm->pc = addr;    // ... move instruction pointer to target procedure address

			printf("\nVM# %d: function call\n", machine_id);

			break;

		case RET:
			rval = POP(_vm);     // pop return value from top of the stack
			_vm->sp = _vm->fp;    // ... return from procedure address ...
			_vm->pc = POP(_vm);   // ... restore instruction pointer ...
			_vm->fp = POP(_vm);   // ... restore framepointer ...
			argc = POP(_vm);     // ... hom many args procedure has ...
			_vm->sp -= argc;     // ... discard all of the args left ...
			PUSH(_vm, rval);     // ... leave return value on top of the stack

			printf("\nVM# %d: function return\n", machine_id);

			break;

		case POP:
			--_vm->sp;      // throw away value at top of the stack

			printf("\nVM# %d: throwing away top of stack\n", machine_id);

			break;

		case PRINT:
			v = POP(_vm);        // pop value from top of the stack ...
			printf("\nVM# %d: Printing top of stack: %d\n", machine_id, v);  // ... and print it					

			break;

		case PAUSE:
			do
			{
				printf("\n\nVM# %d: Paused. Press enter to continue.\n", machine_id); // pause until enter is pressed
			} while (getchar() != '\n');

			break;

		case F_LOAD:                 // load food value
			PUSH(_vm, ((int)stats->food)); // ... push current food value

			printf("\nVM# %d: pushing current food value (%d)\n", machine_id, ((int)stats->food));

			break;

		default:
			break;
		}

	} while (1);
}

VirtualM::VirtualM()
{
	stats = new EntityStats;
}

VirtualM::~VirtualM()
{
	delete stats;
}

void VirtualM::Machine(int* _code)
{
	// initialize virtual machine
	vm = newVM(_code,   // program to execute  
		0,    // start address of main function
		1);    // locals to be reserved
	
	Run(vm);
}

