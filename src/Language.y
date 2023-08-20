
%name-prefix="MAIN"
//%define api.prefix {MAIN} // not working in Bison 3.8.2
%define parse.error verbose

%code provides {
  #define YY_DECL int MAINlex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
}

%type <nodes> globals type_stmts enum_items interface_decls
%type <nodes> stmts elseblock
%type <node> global register interface type type_stmt use
%type <node> function function_decl function_impl returnblock
%type <node> enum enum_item interface_impl
%type <node> simplevar_decl call_or_cast complexvar_set
%type <node> term term2 expr factor stmt condblock whileblock logicexpr
%type <node> logicterm logicfactor TOK_AND TOK_OR event unary
%type <strings> type_impls

%type <ae> element
%type <aes> elements relements array
%type <me> melement
%type <mes> melements matrix

%type <fps> function_params
%type <fp> function_param
%type <pc> paramscall

%type <ident> TOK_IDENTIFIER TOK_XIDENTIFIER ident_or_xident
%type <nint> TOK_INTEGER qualifier
%type <nfloat> TOK_FLOAT
%type <ndouble> TOK_DOUBLE
%type <nldouble> TOK_LDOUBLE
%type <str> TOK_STRING asminline

%%

programa : globals { 
	for(auto stmt : *($globals)) {
		program->addChild(stmt);
	}

	if (errorsfound == 0)
		program->generate(); 
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

use : TOK_USE TOK_IDENTIFIER ';' {
	parseUseFile($2, @TOK_USE);
	$$ = NULL;
}

enum : TOK_ENUM TOK_IDENTIFIER[id] '{' enum_items '}' {
	$$ = new Enum($id, std::move(*$enum_items));
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
	$$ = new NamedConst($id, new Int8($intg));
}

enum_item : TOK_IDENTIFIER[id] {
	$$ = new NamedConst($id);
}

function : function_decl | function_impl

function_decl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' function_params ')' ';' {
				$$ = new FunctionDecl(buildTypes->getType($type, true), $id, $function_params);
				$$->setLocation(@type);
			}

function_impl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' function_params ')' '{' stmts '}'[ef] {
	FunctionImpl *func = new FunctionImpl(buildTypes->getType($type, true), $id, $function_params,
		std::move(*$stmts), @ef); 
	func->setLocation(@type);
	$$ = func;
}

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
	$$ = new FunctionParam($id, buildTypes->getType($type, true));
}

register : TOK_REGISTER TOK_IDENTIFIER[type] TOK_IDENTIFIER[name] TOK_AT expr ';' {
	$$ = new Pointer($name, buildTypes->getType($type, true), $5);
	$$->setQualifier(qvolatile);
	$$->setLocation(@name);
}

interface : TOK_INTF TOK_IDENTIFIER '{' interface_decls[intf] '}' {
	$$ = new Interface($TOK_IDENTIFIER, std::move(*$intf));
	$$->setLocation(@TOK_INTF);
}

interface : TOK_INTF TOK_IDENTIFIER '{' '}' {
	$$ = new Interface($TOK_IDENTIFIER);
	$$->setLocation(@TOK_INTF);
}

interface_decls : interface_decls function_decl {
	$1->push_back($function_decl);
	$$ = $1;
}

interface_decls : function_decl {
	$$ = new vector<Node*>();
	$$->push_back($function_decl);
}

//FIXME: Interface only allows function_decls!
interface_impl : TOK_IDENTIFIER[id] '=' TOK_IDENTIFIER[intfname] '{' type_stmts '}' {
	vector<string> intf;
	intf.push_back($intfname);
	UserType *ut = new UserType($id, std::move(*$type_stmts), std::move(intf));
	ut->setLocation(@id);
	$$ = ut;
}

type : TOK_TYPE TOK_IDENTIFIER TOK_IMPL type_impls '{' type_stmts '}' {
	UserType *ut = new UserType($TOK_IDENTIFIER, std::move(*$type_stmts), std::move(*$type_impls));
	ut->setLocation(@TOK_TYPE);
	$$ = ut;
}

type : TOK_TYPE TOK_IDENTIFIER '{' type_stmts '}' {
	UserType *ut = new UserType($TOK_IDENTIFIER, std::move(*$type_stmts));
	ut->setLocation(@TOK_TYPE);
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

simplevar_decl : TOK_IDENTIFIER[id] '=' expr	{ $$ = new Scalar($id, $expr);   $$->setLocation(@id); }
simplevar_decl : TOK_IDENTIFIER[id] '=' array	{ $$ = new Array($id, $array);   $$->setLocation(@id); }
simplevar_decl : TOK_IDENTIFIER[id] '=' matrix	{ $$ = new Matrix($id, $matrix); $$->setLocation(@id); }

array : '{' elements '}'	{ $$ = $elements; }
matrix : '{' melements '}'	{ $$ = $melements; }

melements : melements ',' melement {
	$1->append($3);
	$$ = $1;
}

melements : melement {
	MatrixElements *mes = new MatrixElements();
	mes->append($1);
	$$ = mes;
}

melement : relements ':' TOK_INTEGER	{ $$ = new MatrixElement($1, (unsigned)$3); }
	     | relements					{ $$ = new MatrixElement($1, 1);}
	 
relements : '{' elements '}'			{ $$ = $2; }

elements : elements ',' element			{ $1->append($3);
										  $$ = $1; }
		 | element						{ ArrayElements *aes = new ArrayElements();
										  aes->append($1);
										  $$ = aes; }

element : expr ':' TOK_INTEGER		{ $$ = new ArrayElement($1, (unsigned)$3); }
        | expr						{ $$ = new ArrayElement($1, 1); }
	
asminline : TOK_ASM TOK_STRING { $$ = $2; }

stmts : stmts stmt {
	$1->push_back($stmt);
}

stmts : stmt {
	$$ = new vector<Node*>();
	$$->push_back($stmt);
	$stmt->setLocation(@stmt);
}

stmt : ident_or_xident '+' '+' ';'					{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', new Int8(1))); }
	 | ident_or_xident '-' '-' ';'					{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', new Int8(1))); }
	 | ident_or_xident '+' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', $4)); }
	 | ident_or_xident '-' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', $4)); }
	 | ident_or_xident '*' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '*', $4)); }
	 | ident_or_xident '/' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '/', $4)); }
	 | ident_or_xident '|' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '|', $4)); }
	 | ident_or_xident '&' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '&', $4)); }
	 | ident_or_xident '^' '=' expr ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '^', $4)); }
	 | ident_or_xident '[' expr ']' '=' expr ';'	{ $$ = new UpdateArray($1, $3, $6);}
	 | ident_or_xident '[' expr ']' '[' expr ']' '=' expr ';'	{ $$ = new UpdateMatrix($1, $3, $6, $9); }
	 | asminline ';'											{ $$ = new InlineAssembly($1); $$->setLocation(@1); }
	 | qualifier simplevar_decl ';'								{ $$ = $2; $$->setQualifier((DataQualifier)$1); }
	 | simplevar_decl ';'
	 | complexvar_set ';'
	 | returnblock ';'
	 | call_or_cast ';'
	 | condblock
	 | whileblock
	 | interface_impl

complexvar_set : TOK_XIDENTIFIER[id] '=' expr		{ $$ = new Scalar($id, $expr);   $$->setLocation(@id); }
complexvar_set : TOK_XIDENTIFIER[id] '=' array		{ $$ = new Array($id, $array);   $$->setLocation(@id); }
complexvar_set : TOK_XIDENTIFIER[id] '=' matrix		{ $$ = new Matrix($id, $matrix); $$->setLocation(@id); }

returnblock : TOK_RETURN expr			{ $$ = new Return($2); }
returnblock : TOK_RETURN logicexpr		{ $$ = new Return($2); }
returnblock : TOK_RETURN				{ $$ = new Return(); }

/*
 * Conditional
 */

condblock : TOK_IF logicexpr '{' stmts '}' {
	$logicexpr->setLocation(@logicexpr);
	$$ = new If($logicexpr, std::move(*$stmts));
	$$->setLocation(@TOK_IF);
}
condblock : TOK_IF logicexpr '{' stmts '}' elseblock {
	$logicexpr->setLocation(@logicexpr);
	$$ = new If($logicexpr, std::move(*$stmts), std::move(*$elseblock));
	$$->setLocation(@TOK_IF);
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
	$$ = new While($logicexpr, std::move(*$stmts));
	$$->setLocation(@TOK_WHILE);
}

whileblock : TOK_WHILE logicexpr ';' {
	$logicexpr->setLocation(@logicexpr);
	$$ = new While($logicexpr);
	$$->setLocation(@TOK_WHILE);
}

whileblock : TOK_LOOP '{' stmts '}' {
	$$ = new Loop(std::move(*$stmts));
	$$->setLocation(@TOK_LOOP);
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
			;

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

factor : '(' expr ')'			{ $$ = $2; }
	   | ident_or_xident		{ $$ = new Load($1); }
	   | TOK_TRUE				{ $$ = new Int1(1); }
	   | TOK_FALSE				{ $$ = new Int1(0); }
	   | TOK_INTEGER			{ $$ = getNodeForIntConst($1); }
	   | TOK_FLOAT				{ $$ = new Float($1); }
	   | TOK_DOUBLE				{ $$ = new Double($1); }
	   | TOK_LDOUBLE			{ $$ = new Float128($1); }
	   | ident_or_xident[id] '[' expr ']'				{ $$ = new LoadArray($1, $3);} 
	   | ident_or_xident[id] '[' expr ']' '[' expr ']'	{ $$ = new LoadMatrix($1, $3, $6);}
	   | call_or_cast
	   | unary
	   ;

ident_or_xident: TOK_IDENTIFIER | TOK_XIDENTIFIER

unary : '-' factor	{ $$ = new BinaryOp($2, '*', getNodeForIntConst(-1)); }
	  | '~' factor	{ $$ = new FlipOp($2); }
      ;

call_or_cast : ident_or_xident[id] '(' paramscall ')' {
	if (strncmp("copy", $id, 4) == 0 && $paramscall->getNumParams() == 1)
		$$ = new MemCopy($paramscall->getParamElement(0));
	//else if buildTypes->get($id) && complex, call constructor
	else {
		$$ = new FunctionCall($id, $paramscall);
	}
	$$->setLocation(@id);
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
