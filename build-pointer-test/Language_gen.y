
%locations
%define api.location.type {location_t}
%define api.pure full
%define parse.lac full
%param {yyscan_t scanner}

%code requires {
  #include "BuildTypes.h"
}

%code top {
  #include <stdlib.h>
  #include <limits.h>
  #define SCANNER_OR_VISITOR
  #include "Header.h"
}

%code provides {
  #ifndef YYLTYPE
  #define YYLTYPE location_t
  #endif
  #include "FlexDependencies.h"
}

%token TOK_VOID TOK_RETURN TOK_REGISTER TOK_AT TOK_VOLATILE TOK_CONST TOK_ASM
%token TOK_IF TOK_ELSE
%token TOK_LOOP TOK_WHILE
%token TOK_AND TOK_OR
%token TOK_IDENTIFIER TOK_USE_IDENTIFIER
%token TOK_CHAR TOK_UINTEGER
%token TOK_FLOAT TOK_DOUBLE TOK_LDOUBLE TOK_INTEGER TOK_STRING TOK_TRUE TOK_FALSE
%token TOK_FINT8 TOK_FINT16 TOK_FINT32 TOK_FINT64
%token TOK_FFLOAT TOK_FDOUBLE TOK_FCHAR TOK_FLONG TOK_FUNSIGNED TOK_FBOOL
%token TOK_TYPE TOK_INTF TOK_IMPL TOK_USE TOK_ENUM

%token TOK_BIND TOK_TO TOK_SINGLETON TOK_TRANSIENT

%token TOK_QUANDO TOK_ESTA
%token EQ_OP NE_OP GE_OP LE_OP GT_OP LT_OP TOK_LSHIFT TOK_RSHIFT
%token TOK_MUL_ASSIGN

%token TOK_INLINE TOK_NOINLINE TOK_WEAK TOK_SECTION TOK_NAKED TOK_SIGNAL TOK_DEBUGONLY TOK_NOOPT

%union {
	char *ident;
	char *str;
	char ch;
	int64_t nint;
	uint64_t unint;
	DataType dtype;
	float nfloat;
	double ndouble;
	long double nldouble;
	Node *node;
	ArrayElements *aes;
	MatrixElements *mes;
	FunctionParams *fps;
	FunctionAttributes *fattrs;
	FunctionAttribute *fattr;
	ParamsCall *pc;
	vector<Node*> *nodes;
	vector<string> *strings;
	ArrayElement *ae;
	MatrixElement *me;
	Variable *fp;
	LeftValueData *leftvd;
}

%start programa

%name-prefix="MAIN"
//%define api.prefix {MAIN} // not working in Bison 3.8.2
%define parse.error verbose
// enable this to trace the parser. Also, set MAINDebug=1 at Scanner.cpp.
%define parse.trace

%code provides {
  #define YY_DECL int MAINlex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
  Node* get_compound_node(Node *load, char op, Node *right);
  string join_strings(const vector<string>& strings, const string& separator);
}

%type <nodes> globals type_stmts enum_items interface_decls
%type <nodes> stmts stmts_rec elseblock
%type <node> global register interface type type_stmt use
%type <node> function function_decl function_impl returnblock
%type <node> enum enum_item interface_impl
%type <node> var_decl var_decl_stmt
%type <node> expr factor stmt condblock whileblock
%type <node> TOK_AND TOK_OR left_value function_call
%type <node> bind asminline
%type <strings> type_impls string_chain

%type <ae> element
%type <aes> elements relements array
%type <me> melement
%type <mes> melements matrix

%type <fps> function_params
%type <fp> function_param
%type <pc> paramscall

%type <ident> TOK_IDENTIFIER
%type <ch> TOK_CHAR
%type <nint> TOK_INTEGER qualifier bind_scope
%type <unint> TOK_UINTEGER
%type <nfloat> TOK_FLOAT
%type <ndouble> TOK_DOUBLE
%type <nldouble> TOK_LDOUBLE
%type <str> TOK_STRING
%type <fattrs> function_attributes
%type <fattr> function_attribute
%type <leftvd> ident_access array_access matrix_access left_value_base
%type <dtype> pointer_type

/* operator precedences */
%left TOK_OR
%left TOK_AND
%left '|'
%left '^'
%left '&'
%left EQ_OP NE_OP
%left LT_OP GT_OP LE_OP GE_OP
%left TOK_LSHIFT TOK_RSHIFT
%left '+' '-'
%left '*' '/' '%'
%precedence UMINUS UADDRESS UDEREFERENCE '!' '~'

%%

programa : %empty

programa : globals {
	for(auto stmt : *($globals)) {
		program->addChild(stmt);
	}
};

globals : globals global {
	if ($global) {
		$1->push_back($global);
	}
}

globals : global {
	$$ = new vector<Node*>();
	if ($global) {
		$global->setLocation(@global);
		$$->push_back($global);
	}
}

global : use
	   | interface
	   | type
	   | register
	   | function
//	   | event
	   | enum
	   | var_decl
	   | bind

use : TOK_USE string_chain ';' {
	parseUseFile(join_strings(*$string_chain, "."), @TOK_USE);
	$$ = NULL;
}

string_chain : string_chain '.' TOK_IDENTIFIER[id] {
	$$ = $1;
	$$->push_back($id);
}

string_chain : TOK_IDENTIFIER[id] {
	$$ = new vector<string>();
	$$->push_back($id);
}

enum : TOK_ENUM TOK_IDENTIFIER[id] '{' enum_items '}' {
	$$ = new Enum($id, std::move(*$enum_items), @id);
}

enum_items : enum_items[items] ',' enum_item {
	$items->push_back($enum_item);
	$$ = $1;
}

enum_items : enum_item {
	$$ = new vector<Node*>();
	$$->push_back($enum_item);
}

enum_item : TOK_IDENTIFIER[id] '=' TOK_INTEGER[intg] {
	$$ = new NamedConst($id, new Int8($intg, @id));
}

enum_item : TOK_IDENTIFIER[id] '=' '-' TOK_INTEGER[intg] {
	$$ = new NamedConst($id, new Int8($intg * -1, @id));
}

enum_item : TOK_IDENTIFIER[id] '=' TOK_UINTEGER[intg] {
	$$ = new NamedConst($id, new UInt8($intg, @id));
}

enum_item : TOK_IDENTIFIER[id] {
	$$ = new NamedConst($id, @id);
}

function : function_decl | function_impl

function_decl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' function_params ')' function_attributes[fa] ';' {
	FunctionDecl *func = new FunctionDecl(buildTypes->getType($type, true), $id, $function_params, @id);
	func->setAttributes($fa);
	$$ = func;
}

function_decl : pointer_type[type] TOK_IDENTIFIER[id] '(' function_params ')' function_attributes[fa] ';' {
	FunctionDecl *func = new FunctionDecl($type, $id, $function_params, @id);
	func->setAttributes($fa);
	$$ = func;
}

function_impl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' function_params ')' function_attributes[fa] '{' stmts '}'[ef] {
	FunctionImpl *func = new FunctionImpl(buildTypes->getType($type, true), $id, $function_params,
		std::move(*$stmts), @id, @ef); 
	func->setAttributes($fa);
	$$ = func;
}

function_impl : pointer_type[type] TOK_IDENTIFIER[id] '(' function_params ')' function_attributes[fa] '{' stmts '}'[ef] {
	FunctionImpl *func = new FunctionImpl($type, $id, $function_params,
		std::move(*$stmts), @id, @ef);
	func->setAttributes($fa);
	$$ = func;
}

function_attributes: function_attributes[fas] ',' function_attribute[fa] {
	$fas->addAttribute($fa);
	$$ = $fas;
}

function_attributes : function_attribute[fa] {
	$$ = new FunctionAttributes();
	$$->addAttribute($fa);
}

function_attributes : %empty {
	$$ = new FunctionAttributes();
}

function_attribute
	: TOK_WEAK							{ $$ = new FunctionAttribute(fa_weak, ""); }
	| TOK_INLINE						{ $$ = new FunctionAttribute(fa_inline, ""); }
	| TOK_NOINLINE						{ $$ = new FunctionAttribute(fa_noinline, ""); }
	| TOK_NAKED							{ $$ = new FunctionAttribute(fa_naked, ""); }
	| TOK_SIGNAL						{ $$ = new FunctionAttribute(fa_signal, ""); }
	| TOK_DEBUGONLY						{ $$ = new FunctionAttribute(fa_debugonly, ""); }
	| TOK_NOOPT							{ $$ = new FunctionAttribute(fa_noopt, ""); }
	| TOK_SECTION TOK_IDENTIFIER[id]	{ $$ = new FunctionAttribute(fa_section, $id); }

//event : TOK_QUANDO TOK_INTEGER TOK_ESTA TOK_INTEGER '{' stmts '}'[ef] {	
				/*char funcname[100];
				snprintf(funcname, 100, "__callback_int_p%d_e%d", (int)$2, (int)$4);
				vectorglobal.push_back(new AttachInterrupt($2, funcname, $4));
				FunctionParams *fps = new FunctionParams();
				$$ = new FunctionImpl(tvoid, funcname, fps, $6, @ef);*/
//				return 0;
//             }

qualifier : TOK_CONST		{ $$ = qconst; }
		  | TOK_VOLATILE	{ $$ = qvolatile; }

function_params: function_params ',' function_param {
	$1 -> append($3);
	$$ = $1; 
}

function_params: function_param {
	FunctionParams *fps = new FunctionParams();
	fps->append($1);
	$$ = fps; 
}

function_params: %empty {
	FunctionParams *fps = new FunctionParams();
	$$ = fps;
}

function_param : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] {
	$$ = new Variable($id, buildTypes->getType($type, true), @type);
}

function_param : pointer_type[type] TOK_IDENTIFIER[id] {
	$$ = new Variable($id, $type, @id);
}

pointer_type : TOK_IDENTIFIER[type] '*' {
	$$ = buildTypes->getPointerType($type, @type, true);
}

function_param : TOK_IDENTIFIER[type] '[' ']' TOK_IDENTIFIER[id] {
	$$ = new ParamArray($id, $type, @type);
}

function_param : TOK_IDENTIFIER[type] '[' ']' '[' ']' TOK_IDENTIFIER[id] {
	$$ = new ParamMatrix($id, $type, @type);
}

register : TOK_REGISTER TOK_IDENTIFIER[type] TOK_IDENTIFIER[name] TOK_AT expr ';' {
	$$ = new Pointer($name, buildTypes->getType($type, true), $5, @name);
	$$->setQualifier(qvolatile);
}

interface : TOK_INTF TOK_IDENTIFIER[id] '{' interface_decls[intf] '}' {
	$$ = new Interface($id, std::move(*$intf), @id);
}

interface : TOK_INTF TOK_IDENTIFIER[id] '{' '}' {
	$$ = new Interface($id, @id);
}

interface_decls : interface_decls function_decl {
	$1->push_back($function_decl);
	$$ = $1;
}

interface_decls : function_decl {
	$$ = new vector<Node*>();
	$$->push_back($function_decl);
}

interface_impl : TOK_IDENTIFIER[id] TOK_IMPL TOK_IDENTIFIER[intfname] '{' type_stmts '}' {
	vector<string> intf;
	intf.push_back($intfname);
	UserType *ut = new UserType($id, std::move(*$type_stmts), std::move(intf), @id);
	$$ = ut;
}

type : TOK_TYPE TOK_IDENTIFIER[id] TOK_IMPL type_impls '{' type_stmts '}' {
	UserType *ut = new UserType($id, std::move(*$type_stmts), std::move(*$type_impls), @id);
	$$ = ut;
}

type : TOK_TYPE TOK_IDENTIFIER[id] '{' type_stmts '}' {
	UserType *ut = new UserType($id, std::move(*$type_stmts), @id);
	$$ = ut;
}

type_impls : type_impls ',' TOK_IDENTIFIER {
	$1->push_back($TOK_IDENTIFIER);
	$$ = $1;
}

type_impls : TOK_IDENTIFIER {
	$$ = new vector<string>();
	$$->push_back($1);
}

type_stmts : type_stmts type_stmt {
	if ($type_stmt)
		$$->push_back($type_stmt);
}

type_stmts : type_stmt {
	$$ = new vector<Node*>();
	if ($type_stmt)
		$$->push_back($type_stmt);
}

type_stmt : var_decl
          | function_impl
		  | interface_impl
		  | enum

bind : TOK_BIND string_chain[id] TOK_TO string_chain[to] bind_scope[scope] ';' {
	string sid = join_strings(*$id, ".");
	string sto = join_strings(*$to, ".");
	injections.insert({sto, new Injection(sid, sto, BindScope($scope), @id)});
	$$ = NULL;
}

bind_scope : TOK_SINGLETON { $$ = bs_singleton; }
		   | TOK_TRANSIENT { $$ = bs_transient; }

array : '{' elements '}'	{ $$ = $elements; }
matrix : '{' melements '}'	{ $$ = $melements; }

melements : melements ',' melement {
	$1->append($3);
	$$ = $1;
}

melements : melement {
	MatrixElements *mes = new MatrixElements(@melements);
	mes->append($1);
	$$ = mes;
}

melement : relements ':' TOK_INTEGER	{ $$ = new MatrixElement($1, (unsigned)$3); }
	     | relements					{ $$ = new MatrixElement($1, 1);}
	 
relements : '{' elements '}'			{ $$ = $2; }

elements : elements ',' element			{ $1->append($3);
										  $$ = $1; }
		 | element						{ ArrayElements *aes = new ArrayElements(@element);
										  aes->append($1);
										  $$ = aes; }

element : expr ':' TOK_INTEGER		{ $$ = new ArrayElement($1, (unsigned)$3); }
        | expr						{ $$ = new ArrayElement($1, 1); }
	
asminline : TOK_ASM TOK_STRING { $$ = new InlineAssembly($2, @1); }
          | TOK_ASM TOK_STRING ':' TOK_STRING { $$ = new InlineAssembly($2, $4, @1); }

stmts : %empty { $$ = new vector<Node*>(); }
	  | stmts_rec

stmts_rec : stmts_rec stmt {
	$1->push_back($stmt);
}
stmts_rec : stmt {
	$$ = new vector<Node*>();
	$$->push_back($stmt);
	$stmt->setLocation(@stmt);
}

stmt : left_value_base[cl] '+' '+' ';'		{ $$ = new CompoundStore($cl, '+', new Int8(1, @cl)); }
	 | left_value_base[cl] '-' '-' ';'		{ $$ = new CompoundStore($cl, '-', new Int8(1, @cl)); }
	 | left_value_base[cl] '+' '=' expr ';'	{ $$ = new CompoundStore($cl, '+', $expr); }
	 | left_value_base[cl] '-' '=' expr ';'	{ $$ = new CompoundStore($cl, '-', $expr); }
	 | left_value_base[cl] TOK_MUL_ASSIGN expr ';' { $$ = new CompoundStore($cl, '*', $expr); }
	 | left_value_base[cl] '/' '=' expr ';'	{ $$ = new CompoundStore($cl, '/', $expr); }
	 | left_value_base[cl] '|' '=' expr ';'	{ $$ = new CompoundStore($cl, '|', $expr); }
	 | left_value_base[cl] '&' '=' expr ';'	{ $$ = new CompoundStore($cl, '&', $expr); }
	 | left_value_base[cl] '^' '=' expr ';'	{ $$ = new CompoundStore($cl, '^', $expr); }
	 | '*' expr[pointer] '=' expr[value] ';'	{ $$ = new PointerStore($pointer, $value, @pointer); }
	 | var_decl
	 | asminline ';'
	 | returnblock ';'
	 | function_call ';'
	 | condblock
	 | whileblock


var_decl : qualifier var_decl_stmt ';'  { $$ = $2; $$->setQualifier((DataQualifier)$qualifier); }
         | var_decl_stmt  ';'

var_decl_stmt : left_value_base[lv] '=' array		{ $$ = new Array($lv->ident, $array, @lv); }
var_decl_stmt : left_value_base[lv] '=' matrix	{ $$ = new Matrix($lv->ident, $matrix, @lv); }
var_decl_stmt : left_value_base[lv] '=' expr {
	$lv->value->setToStore(true);
	$$ = new Scalar($lv, $expr);
}

var_decl_stmt : pointer_type[type] TOK_IDENTIFIER[id] '=' expr[value] {
	auto *lv = new LeftValueData();
	lv->ident = $id;
	lv->loc = @id;
	Scalar *pointer = new Scalar(lv, $value);
	pointer->setDataType($type);
	$$ = pointer;
}

var_decl_stmt : pointer_type[type] TOK_IDENTIFIER[id] {
	NullPointer *nullValue = new NullPointer($type, @id);
	Scalar *pointer = new Scalar($id, nullValue);
	pointer->setDataType($type);
	$$ = pointer;
}

returnblock : TOK_RETURN expr			{ $$ = new Return($2); }
returnblock : TOK_RETURN				{ $$ = new Return(@1); }

/*
 * Conditional
 */

condblock : TOK_IF expr '{' stmts '}' {
	$expr->setLocation(@expr);
	$$ = new If($expr, std::move(*$stmts), @TOK_IF);
}
condblock : TOK_IF expr '{' stmts '}' elseblock {
	$expr->setLocation(@expr);
	$$ = new If($expr, std::move(*$stmts), std::move(*$elseblock), @TOK_IF);
}

elseblock : TOK_ELSE '{' stmts '}' { $$ = $stmts; }
elseblock : TOK_ELSE condblock { 
	auto *nodes = new vector<Node*>();
	nodes->push_back($condblock);
	$$ = nodes;
}

/*
 * Repetition
 */

whileblock : TOK_WHILE expr '{' stmts '}' {
	$expr->setLocation(@expr);
	$$ = new While($expr, std::move(*$stmts), @TOK_WHILE);
}

whileblock : TOK_WHILE expr ';' {
	$expr->setLocation(@expr);
	$$ = new While($expr, @TOK_WHILE);
}

whileblock : TOK_LOOP '{' stmts '}' {
	$$ = new Loop(std::move(*$stmts), @TOK_LOOP);
}

/*
 * Logic and Arithmetic
 */

// logic
expr: expr[e1] TOK_AND expr[e2]	    { $$ = new BinaryOp($e1, TOK_AND, $e2); }
expr: expr[e1] TOK_OR expr[e2]      { $$ = new BinaryOp($e1, TOK_OR, $e2); }
expr: expr[e1] EQ_OP expr[e2]       { $$ = new CmpOp($e1, EQ_OP, $e2, @EQ_OP); }
expr: expr[e1] NE_OP expr[e2]       { $$ = new CmpOp($e1, NE_OP, $e2, @NE_OP); }
expr: expr[e1] LE_OP expr[e2]		{ $$ = new CmpOp($e1, LE_OP, $e2, @LE_OP); }
expr: expr[e1] GE_OP expr[e2]		{ $$ = new CmpOp($e1, GE_OP, $e2, @GE_OP); }
expr: expr[e1] LT_OP expr[e2]		{ $$ = new CmpOp($e1, LT_OP, $e2, @LT_OP); }
expr: expr[e1] GT_OP expr[e2]		{ $$ = new CmpOp($e1, GT_OP, $e2, @GT_OP); }
expr: '!'[op] expr[e]               { $$ = new CmpOp($e, EQ_OP, new Int1(0, @e), @op); }

// arithmetic
expr: expr[e1] '+' expr[e2]			{ $$ = new BinaryOp($e1, '+', $e2); }
expr: expr[e1] '-' expr[e2]			{ $$ = new BinaryOp($e1, '-', $e2); }
expr: expr[e1] '|' expr[e2]			{ $$ = new BinaryOp($e1, '|', $e2); }
expr: expr[e1] '*' expr[e2]			{ $$ = new BinaryOp($e1, '*', $e2); }
expr: expr[e1] '/' expr[e2]			{ $$ = new BinaryOp($e1, '/', $e2); }
expr: expr[e1] '%' expr[e2]			{ $$ = new BinaryOp($e1, '%', $e2); }
expr: expr[e1] '^' expr[e2]			{ $$ = new BinaryOp($e1, '^', $e2); }
expr: expr[e1] '&' expr[e2]			{ $$ = new BinaryOp($e1, '&', $e2); }
expr: expr[e1] TOK_LSHIFT expr[e2]	{ $$ = new BinaryOp($e1, TOK_LSHIFT, $e2); }
expr: expr[e1] TOK_RSHIFT expr[e2]	{ $$ = new BinaryOp($e1, TOK_RSHIFT, $e2); }
expr: '-' expr[e] %prec UMINUS		{ $$ = new BinaryOp($e, '*', getNodeForIntConst(-1, @e)); }
expr: '~' expr[e]					{ $$ = new FlipOp($e); }
expr: '&' expr[e] %prec UADDRESS		{ $$ = new AddressOf($e, @e); }
expr: '*' expr[e] %prec UDEREFERENCE	{ $$ = new Dereference($e, @e); }
expr: factor

factor : '(' expr[e] ')'		{ $$ = $e; }
	   | TOK_TRUE				{ $$ = new Int1(1, @1); }
	   | TOK_FALSE				{ $$ = new Int1(0, @1); }
	   | TOK_CHAR				{ $$ = new Char($1, @1); }
	   | TOK_INTEGER			{ $$ = getNodeForIntConst($1, @1); }
	   | TOK_UINTEGER			{ $$ = getNodeForUIntConst($1, @1); }
	   | TOK_FLOAT				{ $$ = new Float($1, @1); }
	   | TOK_DOUBLE				{ $$ = new Double($1, @1); }
	   | TOK_LDOUBLE			{ $$ = new Float128($1, @1); }
	   | TOK_STRING				{ $$ = new StringConst("conststr", $1, @1); }
	   | left_value
	   ;

// var
// var[x]
// var[x][y]
// var.field
// var[x].field
// var[x][y].field

left_value : left_value_base[lv]	{ $$ = $lv->value; }
		   | function_call

left_value_base : ident_access
        		| array_access
				| matrix_access

ident_access : TOK_IDENTIFIER[id] {
	auto *lvd = new LeftValueData();
	lvd->ident = $id;
	lvd->loc = @id;
	// temporarily set as a load; can be changed below
	lvd->value = new Load($id, @id);
	$$ = lvd;
}

ident_access : ident_access[lv] '.' TOK_IDENTIFIER[id] {
	$lv->ident = $id;
	$lv->stem = $lv->value;
	$lv->value = new FieldAccess($lv->stem, $id, @id);
	$$ = $lv;
}

ident_access : array_access[lv] '.' TOK_IDENTIFIER[id] {
	$lv->ident = $id;
	$lv->stem = $lv->value;
	$lv->value = new FieldAccess($lv->stem, $id, @id);
	$$ = $lv;
}

ident_access : matrix_access[lv] '.' TOK_IDENTIFIER[id] {
	$lv->ident = $id;
	$lv->stem = $lv->value;
	$lv->value = new FieldAccess($lv->stem, $id, @id);
	$$ = $lv;
}

function_call : ident_access[ia] '(' paramscall ')' {
	if ($ia->stem == NULL) { // is a simple global call
		if ($ia->ident == "copy" && $paramscall->getNumParams() == 1)
			$$ = new MemCopy($paramscall->getParamElement(0));
		else if ($ia->ident == "bitcast" && $paramscall->getNumParams() == 2) {
			Node *nodeTy = $paramscall->getParamElement(1);
			Load *load = dynamic_cast<Load*>(nodeTy);
			if (load && buildTypes->getType(load->getName()) != BuildTypes::undefinedType) {
				DataType dt = buildTypes->getType(load->getName());
				$$ = new BitCast($paramscall->getParamElement(0), dt);
			} else {
				yyerrorcpp("Wrong call to bitcast(var, new_type)", $ia->value);
				$$ = NULL;
			}
		} else {
			$$ = new FunctionCall($ia->ident, $paramscall, @ia);
		}
	} else { // call to a function of a User type
		delete $ia->value; // the last ident is the function name; ignore the previous access
		$$ = new FunctionCall($ia->ident, $paramscall, $ia->stem, @ia);
	}
	$$->setLocation(@ia);
}

array_access : left_value_base[lv] '[' expr ']' {
	$lv->stem = $lv->value;
	$lv->value = new ArrayAccess($lv->stem, $expr);
	$$ = $lv;
}

matrix_access : left_value_base[lv] '[' expr[e1] ']' '[' expr[e2]']' {
	$lv->stem = $lv->value;
	$lv->value = new MatrixAccess($lv->stem, $e1, $e2);
	$$ = $lv;
}

paramscall : paramscall ',' expr {
	$1->append($3);
	$$ = $1;
}

paramscall : expr {
	ParamsCall *pc = new ParamsCall();
	pc->append($1);
	$$ = pc;
}

paramscall : %empty { $$ = new ParamsCall(); }

%%

Node *get_compound_node(Node *load, char op, Node *right) {
	if (dynamic_cast<Load*>(load))
		return new Scalar(load->getName(), new BinaryOp(load, op, right));
	else if (LoadArray *la = dynamic_cast<LoadArray*>(load))
		return new UpdateArray(load->getName(), la->getPosition(), new BinaryOp(load, op, right), load->getLoc());
	else if (LoadMatrix *lm = dynamic_cast<LoadMatrix*>(load))
		return new UpdateMatrix(load->getName(), lm->getPosition(), lm->getPosition2(), new BinaryOp(load, op, right), load->getLoc());
	else
		assert(false && "Unknown load node.");
}

string join_strings(const vector<string>& strings, const string& separator) {
	string result = strings[0];
	for(int i = 1; i < strings.size(); i++)
		result += separator + strings[i];
	return result;
}
