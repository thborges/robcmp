#ifndef __PROGRAM_H__
#define __PROGRAM_H__
#include "Node.h"

class Program {
public:
	Program() {}
	
	void declara_auxiliary_c_funcs();

	void generate(Node *n);
};

#endif
