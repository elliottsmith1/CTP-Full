// stack will have fixed size
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

class VirtualM
{
public:
	VirtualM() = default;
	~VirtualM() = default;

	void Machine();
	void Run(VM* vm);

	VM* newVM(int* code,    // pointer to table containing a bytecode to be executed  
		int pc,             // address of instruction to be invoked as first one - entrypoint/main func
		int datasize);

	void delVM(VM* vm);

	int GetState();

private:

	int state = 0;
	int stack_size = 100;
};

#pragma once
