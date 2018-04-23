#include "VirtualM.h"

VM* VirtualM::newVM(float* _code, int _pc, int _datasize)
{      
	srand(time(NULL)); // get random seed

	// total locals size required to perform a program operations
	vm = (VM*)malloc(sizeof(VM));
	vm->code = _code;
	vm->pc = _pc;
	vm->fp = 0;
	vm->sp = -1;
	vm->locals = (int*)malloc(sizeof(int) * _datasize);
	vm->stack = (float*)malloc(sizeof(float) * stack_size);

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

EntityStats * VirtualM::GetStats()
{
	return stats;
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
	vm->pc = 3;

	do {
		//printf("%d", _vm->pc);

		int opcode = NCODE(_vm);        // fetch
		float v, a, b, random_num, x_pos, y_pos;
		int addr, offset, argc, rval;

		switch (opcode) {   // decode

		case HALT:
			return;  // stop the program

		case CONST_I32:
			v = NCODE(_vm);   // get next value from code ...
			PUSH(_vm, v);     // ... and move it on top of the stack

			//printf("\nVM# %d: pushing constant float (%.2f)\n", machine_id, v);

			break;

		case ADD_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, a + b);    // ... add those two values and put result on top of the stack

			//printf("\nVM# %d: adding %.2f + %.2f (%.2f)\n", machine_id, a, b, (a + b));

			break;

		case SUB_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, a - b);    // ... subtract those two values and put result on top of the stack

			//printf("\nVM# %d: subtracting %.2f - %.2f (%.2f)\n", machine_id, a, b, (a - b));

			break;

		case MUL_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, a * b);    // ... multiply those two values and put result on top of the stack

			//printf("\nVM# %d: multiplying %.2f * %.2f (%.2f)\n", machine_id, a, b, (a*b));

			break;

		case LT_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, (a<b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			//printf("\nVM# %d: %.2f less than %.2f?", machine_id, a, b);

			if (a < b)
			{
				//printf(" (true)\n");
			}
			else
			{
				//printf(" (false)\n");
			}

			break;

		case GT_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, (a>b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			//printf("\nVM# %d: %.2f greater than %.2f?", machine_id, a, b);

			if (a > b)
			{
				//printf(" (true)\n");
			}
			else
			{
				//printf(" (false)\n");
			}

			break;

		case EQ_I32:
			b = POP(_vm);        // get second value from top of the stack ...
			a = POP(_vm);        // ... then get first value from top of the stack ...
			PUSH(_vm, (a == b) ? 1 : 0); // ... compare those two values, and put result on top of the stack

			//printf("\nVM# %d: %.2f equal to %.2f?", machine_id, a, b);

			if (a == b)
			{
				//printf(" (true)\n");
			}
			else
			{
				//printf(" (false)\n");
			}

			break;

		case JMP:
			addr = NCODE(_vm);  // get address pointer from code ...

			//printf("\nVM# %d: jump to opcode instruction: %d\n", machine_id, addr);

			_vm->pc = addr; // ... jump with program counter to provided address
			break;

		case JMPT:
			addr = NCODE(_vm);  // get address pointer from code ...
			if (POP(_vm) == 1)
			{      // ... pop value from top of the stack, and if it's true ...
				_vm->pc = addr; // ... jump with program counter to provided address

				//printf("\nVM# %d: jump true\nopcode: %d\n", machine_id, addr);
			}

			break;

		case JMPF:
			addr = NCODE(_vm);  // get address pointer from code ...
			if (POP(_vm) == 0)
			{      // ... pop value from top of the stack, and if it's true ...
				_vm->pc = addr; // ... jump with program counter to provided address

				//printf("\nVM# %d: jump false\nopcode: %d\n", machine_id, addr);
			}

			break;

		case LOAD:                  // load local value or function arg  
			offset = NCODE(_vm);     // get next value from code to identify local variables offset start on the stack
			PUSH(_vm, _vm->stack[_vm->fp + offset]); // ... put on the top of the stack variable stored relatively to frame pointer

			//printf("\nVM# %d: local load\n", machine_id);

			break;

		case S_LOAD:                 // load state
			PUSH(_vm, state); // ... push current state

			//printf("\nVM# %d: pushing current state (%.2f)\n", machine_id, state);

			break;

		case STORE:                 // store local value or function arg  
			v = POP(_vm);            // get value from top of the stack ...
			offset = NCODE(_vm);     // ... get the relative pointer address from code ...
			_vm->locals[_vm->fp + offset] = v;  // ... and store value at address received relatively to frame pointer

			//printf("\nVM# %d: store locally\n", machine_id);

			break;

		case S_STORE:               // store state
			v = POP(_vm);            // get value from top of the stack ...
			state = v;

			//printf("\nVM# %d: saving state (%.2f)\n", machine_id, v);

			break;

		case GLOAD:
			addr = POP(_vm);             // get pointer address from code ...
			v = _vm->locals[addr];         // ... load value from memory of the provided addres ...
			PUSH(_vm, v);                // ... and put that value on top of the stack

			//printf("\nVM# %d: load global\nvalue: %.2f\naddress: %d\n", machine_id, v, addr);

			break;

		case GSTORE:
			v = POP(_vm);                // get value from top of the stack ...
			addr = NCODE(_vm);           // ... get pointer address from code ...
			_vm->locals[addr] = v;         // ... and store value at address received

			//printf("\nVM# %d: store global\nvalue: %.2f\naddress: %d\n", machine_id, v, addr);

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

			//printf("\nVM# %d: function call\n", machine_id);

			break;

		case RET:
			rval = POP(_vm);     // pop return value from top of the stack
			_vm->sp = _vm->fp;    // ... return from procedure address ...
			_vm->pc = POP(_vm);   // ... restore instruction pointer ...
			_vm->fp = POP(_vm);   // ... restore framepointer ...
			argc = POP(_vm);     // ... hom many args procedure has ...
			_vm->sp -= argc;     // ... discard all of the args left ...
			PUSH(_vm, rval);     // ... leave return value on top of the stack

			//printf("\nVM# %d: function return\n", machine_id);

			break;

		case POP:
			--_vm->sp;      // throw away value at top of the stack

			//printf("\nVM# %d: throwing away top of stack\n", machine_id);

			break;

		case PRINT:
			v = POP(_vm);        // pop value from top of the stack ...
			//printf("\nVM# %d: Printing top of stack: %.2f\n", machine_id, v);  // ... and print it					

			break;

		case PAUSE:
			do
			{
				printf("\n\nVM# %d: Paused. Press enter to continue.\n", machine_id); // pause until enter is pressed
			} while (getchar() != '\n');

			break;

		case STAT_LOAD:
			v = NCODE(_vm);   // get stat id from next value 

			//return stat based on ID selected
			switch ((int)v)
			{
			case 0:
				PUSH(_vm, stats->food); // ... push current food value
				//printf("\nVM# %d: pushing current food value (%.2f)\n", machine_id, stats->food);
				break;
			case 1:
				PUSH(_vm, ((int)stats->food_in_sight)); // ... push current food sight bool
				//printf("\nVM# %d: pushing current food sight bool (%d)\n", machine_id, ((int)stats->food_in_sight));
				break;
			case 2:
				PUSH(_vm, stats->game_objects.size());
				//printf("\nVM# %d: pushing game object vector size (%d)\n", machine_id, stats->game_objects.size());
				break;
			case 3:
				PUSH(_vm, stats->speed); // ... push current speed
				//printf("\nVM# %d: pushing current speed (%.2f)\n", machine_id, stats->speed);
				break;
			case 4:
				PUSH(_vm, stats->health); // ... push current health
				//printf("\nVM# %d: pushing current health (%.2f)\n", machine_id, stats->health);
				break;
			case 5:
				PUSH(_vm, stats->pos_x); // ... push current x pos
				//printf("\nVM# %d: pushing current x pos (%.2f)\n", machine_id, stats->pos_x);
				break;
			case 6:
				PUSH(_vm, stats->pos_y); // ... push current y pos
				//printf("\nVM# %d: pushing current y pos (%.2f)\n", machine_id, stats->pos_y);
				break;
			case 7:
				PUSH(_vm, stats->target_x); // ... push current target x pos
				//printf("\nVM# %d: pushing current x target pos (%.2f)\n", machine_id, stats->target_x);
				break;
			case 8:
				PUSH(_vm, stats->target_y); // ... push current target y pos
				//printf("\nVM# %d: pushing current y target pos (%.2f)\n", machine_id, stats->target_y);
				break;
			case 9:
				PUSH(_vm, stats->nearby_objects.size());
				//printf("\nVM# %d: pushing nearby object vector size (%d)\n", machine_id, stats->nearby_objects.size());
				break;
			case 11:
				PUSH(_vm, stats->sight);
				break;
			case 12:
				PUSH(_vm, stats->thirst);
				break;
			case 13:
				PUSH(_vm, (int)stats->thirsty);
				break;
			}
			break;

		case STAT_SAVE:
			a = POP(_vm);		//get value from stack	
			v = NCODE(_vm);   // get stat id from next value 

			//save stat based on ID selected and value given
			switch ((int)v)
			{
			case 0:
				stats->food = a;
				//printf("\nVM# %d: saving food value (%.2f)\n", machine_id, stats->food);
				break;
			case 1:
				stats->food_in_sight = a;
				//printf("\nVM# %d: saving food sight bool (%d)\n", machine_id, ((int)stats->food_in_sight));
				break;
			case 3:
				stats->speed = a;
				//printf("\nVM# %d: saving speed (%.2f)\n", machine_id, stats->speed);
				break;
			case 4:
				stats->health = a;
				//printf("\nVM# %d: saving health (%.2f)\n", machine_id, stats->health);
				break;
			case 5:
				stats->pos_x = a;
				//printf("\nVM# %d: saving pos x (%.2f)\n", machine_id, stats->pos_x);
				break;
			case 6:
				stats->pos_y = a;
				//printf("\nVM# %d: saving pos y (%.2f)\n", machine_id, stats->pos_y);
				break;
			case 7:
				stats->target_x = a;
				//printf("\nVM# %d: saving target x (%.2f)\n", machine_id, stats->target_x);
				break;
			case 8:
				stats->target_y = a;
				//printf("\nVM# %d: saving target y (%.2f)\n", machine_id, stats->target_y);
				break;
			case 11:
				stats->sight - a;
				break;
			case 12:
				stats->thirst = a;
				break;
			case 13:
				if (a == 0)
				{
					stats->thirsty = false;
				}

				else if (a == 1)
				{
					stats->thirsty = true;
				}				
				break;
			}
			break;

		case RAND:
			v = NCODE(_vm);   // get range from next value			
			random_num = rand() % (int)v; // get random int between 0 and range max
			//printf("\nVM# %d: pushing random value (%.2f)\n", machine_id, random_num);
			PUSH(_vm, random_num);	//return value
			break;

		case CHECK_NEAR:
			b = POP(_vm);        
			a = POP(_vm);
			//printf("\nVM# %d: check if (%.2f) is near (%.02f) \n", machine_id, a, b);

			if ((a < (b + 60)) && (a > (b - 60)))
			{				
				PUSH(_vm, 1);
			}
			else
			{
				PUSH(_vm, 0);
			}
			break;

		case GET_X_POS:
			v = POP(_vm);   // get id from next value
			x_pos = stats->nearby_objects[v]->getPosition().x;
			//printf("\nVM# %d: pushing x position (%.02f) \n", machine_id, x_pos);
			PUSH(_vm, x_pos);
			break;

		case GET_Y_POS:
			v = POP(_vm);   // get id from next value
			y_pos = stats->nearby_objects[v]->getPosition().y;
			//printf("\nVM# %d: pushing y position (%.02f) \n", machine_id, y_pos);
			PUSH(_vm, y_pos);
			break;

		case CHECK_COLOUR:
			v = POP(_vm);   // get id 
			//printf("\nVM# %d: checking (%d) nearby object colour\n", machine_id, v);

			if (stats->nearby_objects[v]->getFillColor() == sf::Color(255, 102, 0, 255))
			{
				PUSH(_vm, 1);

				stats->food_tile = stats->nearby_objects[v];
			}

			else if (stats->nearby_objects[v]->getFillColor() == sf::Color::Green)
			{
				PUSH(_vm, 2);
			}

			else if (stats->nearby_objects[v]->getFillColor() == sf::Color::Blue)
			{
				PUSH(_vm, 3);
			}

			else if (stats->nearby_objects[v]->getFillColor() == sf::Color::Red)
			{
				PUSH(_vm, 4);
			}

			break;

		case CHANGE_COLOUR:					
			v = POP(_vm);		// get colour id
			a = NCODE(_vm);   // get id from next value			
			//printf("\nVM# %d: changing nearby object (%d) colour\n", machine_id, v);

			switch ((int)a)
			{
			case 0:
				stats->nearby_objects[v]->setFillColor(sf::Color::Green);
				break;
			case 1:
				stats->nearby_objects[v]->setFillColor(sf::Color::Red);
				break;
			default:
				break;
			}
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

void VirtualM::Machine(float* _code)
{
	// initialize virtual machine
	vm = newVM(_code,   // program to execute  
		3,    // start address of main function
		0);    // locals to be reserved
	
	//Run(vm);
}

