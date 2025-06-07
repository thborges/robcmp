
%name-prefix="MAIN"
//%define api.prefix {MAIN} // not working in Bison 3.8.2
%define parse.error verbose

%code provides {
  #define YY_DECL int MAINlex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
}

%type <nodes> globals type_stmts enum_items interface_decls
%type <nodes> stmts stmts_rec elseblock
%type <node> global register interface type type_stmt use
%type <node> function function_decl function_impl returnblock
%type <node> enum enum_item interface_impl
%type <node> simplevar_decl call_or_cast complexvar_set
%type <node> term term2 expr factor stmt condblock whileblock logicexpr
%type <node> logicterm logicfactor TOK_AND TOK_OR event unary logicunary
%type <node> bind asminline
%type <strings> type_impls

%type <ae> element
%type <aes> elements relements array
%type <me> melement
%type <mes> melements matrix

%type <fps> function_params
%type <fp> function_param
%type <pc> paramscall

%type <ident> TOK_IDENTIFIER TOK_XIDENTIFIER ident_or_xident
%type <ch> TOK_CHAR
%type <nint> TOK_INTEGER qualifier bind_scope
%type <unint> TOK_UINTEGER
%type <nfloat> TOK_FLOAT
%type <ndouble> TOK_DOUBLE
%type <nldouble> TOK_LDOUBLE
%type <str> TOK_STRING
%type <fattrs> function_attributes
%type <fattr> function_attribute

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
	   | event
	   | enum
	   | simplevar_decl ';'
	   | qualifier simplevar_decl ';'	{ $$ = $2; $$->setQualifier((DataQualifier)$1); }
	   | bind

use : TOK_USE TOK_IDENTIFIER ';' {
	parseUseFile($2, @TOK_USE);
	$$ = NULL;
}

use : TOK_USE TOK_XIDENTIFIER ';' {
	parseUseFile($2, @TOK_USE);
	$$ = NULL;
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

function_impl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' function_params ')' function_attributes[fa] '{' stmts '}'[ef] {
	FunctionImpl *func = new FunctionImpl(buildTypes->getType($type, true), $id, $function_params,
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

event : TOK_QUANDO TOK_INTEGER TOK_ESTA TOK_INTEGER '{' stmts '}'[ef] {	
				/*char funcname[100];
				snprintf(funcname, 100, "__callback_int_p%d_e%d", (int)$2, (int)$4);
				vectorglobal.push_back(new AttachInterrupt($2, funcname, $4));
				FunctionParams *fps = new FunctionParams();
				$$ = new FunctionImpl(tvoid, funcname, fps, $6, @ef);*/
				return 0;
             }
		   ;

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

type_stmt : simplevar_decl ';'
		  | qualifier[q] simplevar_decl ';'	{ $simplevar_decl->setQualifier((DataQualifier)$q); $$ = $2; }
          | function_impl
		  | interface_impl
		  | enum

simplevar_decl : TOK_IDENTIFIER[id] '=' logicexpr	{ $$ = new Scalar($id, $logicexpr);	$$->setLocation(@id); }
simplevar_decl : TOK_IDENTIFIER[id] '=' array		{ $$ = new Array($id, $array, @id); }
simplevar_decl : TOK_IDENTIFIER[id] '=' matrix		{ $$ = new Matrix($id, $matrix, @id); }

bind : TOK_BIND ident_or_xident[id] TOK_TO ident_or_xident[to] bind_scope[scope] ';' {
	injections.insert({$to, new Injection($id, $to, BindScope($scope), @id)});
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

stmt : ident_or_xident '+' '+' ';'					{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '+', new Int8(1, @1))); }
	 | ident_or_xident '-' '-' ';'					{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '-', new Int8(1, @1))); }
	 | ident_or_xident '+' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '+', $4)); }
	 | ident_or_xident '-' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '-', $4)); }
	 | ident_or_xident '*' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '*', $4)); }
	 | ident_or_xident '/' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '/', $4)); }
	 | ident_or_xident '|' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '|', $4)); }
	 | ident_or_xident '&' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '&', $4)); }
	 | ident_or_xident '^' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1, @1), '^', $4)); }
	 | ident_or_xident '[' expr ']' '=' expr ';'	{ $$ = new UpdateArray($1, $3, $6, @1);}
	 
	 | ident_or_xident '[' expr ']' '[' expr ']' '=' expr ';'	{ $$ = new UpdateMatrix($1, $3, $6, $9, @1); }
	 | ident_or_xident[id] '[' expr[e1] ']' '[' expr[e2] ']' '&' '=' expr[e3] ';'	{
			Node *bop = new BinaryOp(new LoadMatrix($id, $e1, $e2, @id), '&', $e3);
			$$ = new UpdateMatrix($id, $e1, $e2, bop, @1);
	   }
	 | ident_or_xident[id] '[' expr[e1] ']' '[' expr[e2] ']' '|' '=' expr[e3] ';'	{
			Node *bop = new BinaryOp(new LoadMatrix($id, $e1, $e2, @id), '|', $e3);
			$$ = new UpdateMatrix($id, $e1, $e2, bop, @1);
	   }
	 | asminline ';'											{ $$ = $1; }
	 | qualifier simplevar_decl ';'								{ $$ = $2; $$->setQualifier((DataQualifier)$1); }
	 | simplevar_decl ';'
	 | complexvar_set ';'
	 | returnblock ';'
	 | call_or_cast ';'
	 | condblock
	 | whileblock
	 | interface_impl

complexvar_set : TOK_XIDENTIFIER[id] '=' logicexpr	{ $$ = new Scalar($id, $logicexpr);	$$->setLocation(@id); }
complexvar_set : TOK_XIDENTIFIER[id] '=' array		{ $$ = new Array($id, $array, @id); }
complexvar_set : TOK_XIDENTIFIER[id] '=' matrix		{ $$ = new Matrix($id, $matrix, @id); }

returnblock : TOK_RETURN logicexpr		{ $$ = new Return($2); }
returnblock : TOK_RETURN				{ $$ = new Return(@1); }

/*
 * Conditional
 */

condblock : TOK_IF logicexpr '{' stmts '}' {
	$logicexpr->setLocation(@logicexpr);
	$$ = new If($logicexpr, std::move(*$stmts), @TOK_IF);
}
condblock : TOK_IF logicexpr '{' stmts '}' elseblock {
	$logicexpr->setLocation(@logicexpr);
	$$ = new If($logicexpr, std::move(*$stmts), std::move(*$elseblock), @TOK_IF);
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

whileblock : TOK_WHILE logicexpr '{' stmts '}' {
	$logicexpr->setLocation(@logicexpr);
	$$ = new While($logicexpr, std::move(*$stmts), @TOK_WHILE);
}

whileblock : TOK_WHILE logicexpr ';' {
	$logicexpr->setLocation(@logicexpr);
	$$ = new While($logicexpr, @TOK_WHILE);
}

whileblock : TOK_LOOP '{' stmts '}' {
	$$ = new Loop(std::move(*$stmts), @TOK_LOOP);
}

/*
 * Logic
 */

logicexpr : logicexpr TOK_OR logicterm		{ $$ = new BinaryOp($1, TOK_OR, $3); }
		  | logicterm						{ $$ = $1; }
		  ;

logicterm : logicterm TOK_AND logicfactor	{ $$ = new BinaryOp($1, TOK_AND, $3); }
		  | logicfactor						{ $$ = $1; }
		  ;

logicfactor : '(' logicexpr ')'		{ $$ = $2; }
			| expr '=''=' expr		{ $$ = new CmpOp($1, EQ_OP, $4); }
			| expr '!''=' expr		{ $$ = new CmpOp($1, NE_OP, $4); }
			| expr '<''=' expr		{ $$ = new CmpOp($1, LE_OP, $4); }
			| expr '>''=' expr		{ $$ = new CmpOp($1, GE_OP, $4); }
			| expr '<' expr			{ $$ = new CmpOp($1, LT_OP, $3); }
			| expr '>' expr			{ $$ = new CmpOp($1, GT_OP, $3); }
			| expr %expect 1
			| logicunary
			;

logicunary : '!' logicfactor { $$ = new BinaryOp(new Int1(1, @2), '-', $2); }

/*
 * Arithmetic
 */

expr : expr '+' term			{ $$ = new BinaryOp($1, '+', $3); }
	 | expr '-' term			{ $$ = new BinaryOp($1, '-', $3); }
	 | expr '|' term			{ $$ = new BinaryOp($1, '|', $3); }
	 | expr TOK_LSHIFT term		{ $$ = new BinaryOp($1, TOK_LSHIFT, $3); }
	 | expr TOK_RSHIFT term		{ $$ = new BinaryOp($1, TOK_RSHIFT, $3); }
	 | term						{ $$ = $1; }
	 ;

term : term '*' term2		{ $$ = new BinaryOp($1, '*', $3); }
	 | term '/' term2		{ $$ = new BinaryOp($1, '/', $3); }
	 | term '%' term2		{ $$ = new BinaryOp($1, '%', $3); }
	 | term '^' term2		{ $$ = new BinaryOp($1, '^', $3); }
	 | term2				{ $$ = $1; }
	 ;

term2 : term2 '&' factor    { $$ = new BinaryOp($1, '&', $3); }
	  | factor				{ $$ = $1; }
	  ;

factor : '(' expr ')' 			{ $$ = $2; }
	   | ident_or_xident		{ $$ = new Load($1, @1); }
	   | TOK_TRUE				{ $$ = new Int1(1, @1); }
	   | TOK_FALSE				{ $$ = new Int1(0, @1); }
	   | TOK_CHAR				{ $$ = new Char($1, @1); }
	   | TOK_INTEGER			{ $$ = getNodeForIntConst($1, @1); }
	   | TOK_UINTEGER			{ $$ = getNodeForUIntConst($1, @1); }
	   | TOK_FLOAT				{ $$ = new Float($1, @1); }
	   | TOK_DOUBLE				{ $$ = new Double($1, @1); }
	   | TOK_LDOUBLE			{ $$ = new Float128($1, @1); }
	   | TOK_STRING				{ $$ = new StringConst("conststr", $1, @1); }
	   | ident_or_xident[id] '[' expr ']'				{ $$ = new LoadArray($1, $3, @id);} 
	   | ident_or_xident[id] '[' expr ']' '[' expr ']'	{ $$ = new LoadMatrix($1, $3, $6, @id);}
	   | call_or_cast
	   | unary
	   ;

ident_or_xident: TOK_IDENTIFIER | TOK_XIDENTIFIER

unary : '-' factor	{ $$ = new BinaryOp($factor, '*', getNodeForIntConst(-1, @factor)); }
	  | '~' factor	{ $$ = new FlipOp($factor); }
      ;

call_or_cast : ident_or_xident[id] '(' paramscall ')' {
	if (strncmp("copy", $id, 4) == 0 && $paramscall->getNumParams() == 1)
		$$ = new MemCopy($paramscall->getParamElement(0));
	else if (strncmp("bitcast", $id, 7) == 0 && $paramscall->getNumParams() == 2) {
		Node *nodeTy = $paramscall->getParamElement(1);
		Load *load = dynamic_cast<Load*>(nodeTy);
		if (load && buildTypes->getType(load->getName()) != BuildTypes::undefinedType) {
			DataType dt = buildTypes->getType(load->getName());
			$$ = new BitCast($paramscall->getParamElement(0), dt);
		} else {
			$$ = new FunctionCall($id, $paramscall, @id);
		}
	} else {
		$$ = new FunctionCall($id, $paramscall, @id);
	}
	$$->setLocation(@id);
}

paramscall : paramscall ',' logicexpr {
	$1->append($3);
	$$ = $1;
}

paramscall : logicexpr {
	ParamsCall *pc = new ParamsCall();
	pc->append($1);
	$$ = pc;
}

paramscall : %empty { $$ = new ParamsCall(); }

%%
