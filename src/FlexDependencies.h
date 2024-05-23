
#pragma once

#include <cstdint>

#include <vector>
#include <string>
using namespace std;

class Node;
class Stmts;
class ArrayElements;
class MatrixElements;
class FunctionParams;
class ParamsCall;
class Structure;
class ArrayElement;
class MatrixElement;
class Variable;
class Field;

#include "SourceLocation.h"
#include "Colors.h"

typedef void* yyscan_t;

#ifdef __MINGW64__
char* strndup(const char *src, size_t size);
#endif

