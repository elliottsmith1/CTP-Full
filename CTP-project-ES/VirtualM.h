
#define PUSH(vm, v) vm->stack[++vm->sp] = v // push value on top of the stack
#define POP(vm)     vm->stack[vm->sp--]     // pop value from top of the stack
#define NCODE(vm)   vm->code[vm->pc++]      // get next bytecode

typedef struct {
	int* locals;    // local scoped data
	int* code;      // array od byte codes to be executed
	int* stack;     // virtual stack
	int pc;         // program counter (aka. IP - instruction pointer)
	int sp;         // stack pointer
	int fp;         // frame pointer (for local scope)
} VM;

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
	CONST_I32 = 10, // push constant integer
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
	RET = 21,       // return from procedure
	PAUSE = 22		// pause program
};

class VirtualM
{
public:
	VirtualM() = default;
	~VirtualM() = default;

	void Machine(int* _code);
	void Run(VM* vm);

	VM* newVM(int* code,    // pointer to table containing a bytecode to be executed  
		int pc,             // address of instruction to be invoked as first one - entrypoint/main func
		int datasize);

	void delVM(VM* vm);

	int GetState();
	int GetID();
	VM* GetVM();

	void SetID(int _id);	

private:

	VM* vm;

	int state = 0;
	int stack_size = 100;
	int machine_id = 0;
};

#pragma once
