
%name-prefix="USE"
//%define api.prefix {USE} // not working in Bison 3.8.2
%define parse.error verbose

// enable this to trace the parser. Also, set USEDebug=1 at Scanner.cpp.
%define parse.trace

%code provides {
  #define YY_DECL int USElex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
}

%type <nodes> globals type_stmts enum_items interface_decls
%type <nodes> stmts
%type <node> global register interface type type_stmt use
%type <node> function function_decl function_impl
%type <node> enum enum_item const_expr expr unary interface_impl
%type <node> simplevar_decl cast constructor
%type <node> ignore_stmt ignore_param ignore
%type <strings> type_impls

%type <ae> element
%type <aes> elements relements array
%type <me> melement
%type <mes> melements matrix

%type <fps> function_params
%type <fp> function_param

%type <ident> TOK_IDENTIFIER TOK_XIDENTIFIER
%type <nint> TOK_INTEGER qualifier
%type <unint> TOK_UINTEGER
%type <nfloat> TOK_FLOAT
%type <ndouble> TOK_DOUBLE
%type <nldouble> TOK_LDOUBLE
%type <ch> TOK_CHAR

%type <fattrs> function_attributes
%type <fattr> function_attribute

%printer { fprintf(yyo, "'%s'", $$); } <ident>
%printer { fprintf(yyo, "'%s'", $$ ? $$->getName().c_str() : ""); } <node>

%%

programa : globals {
	for(auto stmt : *($globals)) {
		program->addChild(stmt);
	}
}

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
	   | enum
	   | simplevar_decl ';' { $$ = NULL; } // don't export global vars

global : qualifier simplevar_decl ';' {
	if ($qualifier == qconst)
		$$ = $simplevar_decl;
	else
		$$ = NULL;
}

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
	$$ = new NamedConst($id, new Int8($intg, @intg), @id);
}

enum_item : TOK_IDENTIFIER[id] '=' '-' TOK_INTEGER[intg] {
	$$ = new NamedConst($id, new Int8($intg * -1, @intg), @id);
}

enum_item : TOK_IDENTIFIER[id] '=' TOK_UINTEGER[intg] {
	$$ = new NamedConst($id, new UInt8($intg, @intg), @id);
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
	vector<Node*> stmts;
	FunctionImpl *func = new FunctionImpl(buildTypes->getType($type, true), $id, $function_params,
		std::move(stmts), @type, @ef);
	func->setExternal(true);
	func->setDeclaration(true);
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
	| TOK_SECTION TOK_IDENTIFIER[id]	{ $$ = new FunctionAttribute(fa_section, $id); }

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

register : TOK_REGISTER TOK_IDENTIFIER[type] TOK_IDENTIFIER[name] TOK_AT const_expr ';' {
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
	ut->setDeclaration(true);
	$$ = ut;
}

type : TOK_TYPE TOK_IDENTIFIER[id] '{' type_stmts '}' {
	UserType *ut = new UserType($id, std::move(*$type_stmts), @id);
	ut->setDeclaration(true);
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
simplevar_decl : TOK_IDENTIFIER[id] '=' array	{ $$ = new Array($id, $array, @id); }
simplevar_decl : TOK_IDENTIFIER[id] '=' matrix	{ $$ = new Matrix($id, $matrix, @id); }

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

const_expr : TOK_INTEGER    { $$ = getNodeForIntConst($1, @1); }
		   | TOK_UINTEGER   { $$ = getNodeForUIntConst($1, @1); }
		   | TOK_CHAR       { $$ = new Char($1, @1); }
           | TOK_TRUE		{ $$ = new Int1(1, @1); }
           | TOK_FALSE		{ $$ = new Int1(0, @1); }
		   | TOK_FLOAT		{ $$ = new Float($1, @1); }
		   | TOK_DOUBLE		{ $$ = new Double($1, @1); }
		   | TOK_LDOUBLE	{ $$ = new Float128($1, @1); }
		   | unary			{ $$ = $1; }
		   //TODO: Add other constant nodes here!
		   
unary : '-' const_expr	{ $$ = new BinaryOp($const_expr, '*', getNodeForIntConst(-1, @const_expr)); }
	  | '~' const_expr	{ $$ = new FlipOp($const_expr); }
      ;

expr : const_expr
	 | cast
	 | constructor
	 //TODO: Add other expr nodes here!

cast : TOK_IDENTIFIER[id] '(' ignore_param ')' {
	ParamsCall *pc = new ParamsCall();
	pc->append(new Node(@id));
	$$ = new FunctionCall($id, pc, @id);
	$$->setLocation(@id);
}

constructor : TOK_IDENTIFIER[id] '(' ')' {
	ParamsCall *pc = new ParamsCall();
	pc->append(new Node(@id));
	$$ = new FunctionCall($id, pc, @id);
	$$->setLocation(@id);
}

ignore_param : ignore_p	{ $$ = NULL; }
			 | error	{ $$ = NULL; }

/* put here any symbol that can start a expr.
 * to be precise, the FIRST(expr)
 */
ignore_p : TOK_INTEGER		{ YYERROR; }
		 | TOK_IDENTIFIER	{ YYERROR; }
		 
stmts : stmts ignore_stmt	{ $$ = NULL; }
	  | ignore_stmt			{ $$ = NULL; }

ignore_stmt : ignore				{ $$ = NULL; }
			| error '{' stmts '}'	{ $$ = NULL; }
		    | error	';'				{ $$ = NULL; }

/* put here any symbol that can start a stmt (except globals).
 * to be precise, the FIRST(stmt) of Language.y
 */
ignore : TOK_IDENTIFIER  { YYERROR; }
	   | TOK_XIDENTIFIER { YYERROR; }
	   | TOK_WHILE       { YYERROR; }
	   | TOK_RETURN      { YYERROR; }
	   | TOK_CONST       { YYERROR; }
	   | TOK_VOLATILE    { YYERROR; }
	   | TOK_IF          { YYERROR; }
	   | TOK_ELSE        { YYERROR; }
	   | TOK_LOOP        { YYERROR; }
	   | TOK_ASM         { YYERROR; }

%%

/*static const char *
error_format_string (int argc)
{
  switch (argc)
    {
    default: // Avoid compiler warnings.
    case 0: return "%@: syntax error";
    case 1: return "%@: syntax error: unexpected %u";
      // TRANSLATOR '%@' is a location in a file, '%u' is an
      // "unexpectetoken", and '%0e', '%1e'... are expected tokens
      // at this pot.
      //
      // For instan on the expression "1 + * 2", you'd get
      //
      // 1.5: syntaerror: expected - or ( or number or function or variable before *
    case 2: return "%@: syntax error: expected %0e before %u";
    case 3: return "%@: syntax error: expected %0e or %1e before %u";
    case 4: return "%@: syntax error: expected %0e or %1e or %2e before %u";
    case 5: return "%@: syntax error: expected %0e or %1e or %2e or %3e before %u";
    case 6: return "%@: syntax error: expected %0e or %1e or %2e or %3e or %4e before %u";
    case 7: return "%@: syntax error: expected %0e or %1e or %2e or %3e or %4e or %5e before %u";
    case 8: return "%@: syntax error: expected %0e or %1e or %2e or %3e or %4e or %5e etc., before %u";
    }
}

static int yyreport_syntax_error (const yypcontext_t *ctx, yyscan_t scanner) {
	enum { ARGS_MAX = 6 };
	yysymbol_kind_t arg[ARGS_MAX];
	
	int argsize = yypcontext_expected_tokens (ctx, arg, ARGS_MAX);
	if (argsize < 0)
		return argsize;

	const int too_many_expected_tokens = argsize == 0 && arg[0] != YYSYMBOL_YYEMPTY;
	if (too_many_expected_tokens)
		argsize = ARGS_MAX;
	
	const char *format = error_format_string (1 + argsize + too_many_expected_tokens);

	const YYLTYPE *loc = yypcontext_location (ctx);
	while (*format) {
		// %@: location.
		if (format[0] == '%' && format[1] == '@') {
			fprintf(stderr, "%s:%d:%d:", build_filename(),
					loc->first_line, loc->first_column);
			format += 2;
		}
	// %u: unexpected token.
		else if (format[0] == '%' && format[1] == 'u') {
			fputs (yysymbol_name (yypcontext_token (ctx)), stderr);
			format += 2;
		}
	// %0e, %1e...: expected token.
		else if (format[0] == '%' && isdigit ((unsigned char) format[1])
			&& format[2] == 'e' && (format[1] - '0') < argsize) {
			
			int i = format[1] - '0';
			fputs (yysymbol_name (arg[i]), stderr);
			format += 3;
		} else {
			fputc (*format, stderr);
			++format;
		}
	}
	fputc ('\n', stderr);

	// Quote the source line.
	{
		fprintf (stderr, "%5d | %s\n", loc->first_line, uctx->line);
		fprintf (stderr, "%5s | %*s", "", loc->first_column, "^");
		for (int i = loc->last_column - loc->first_column - 1; 0 < i; --i)
			putc ('~', stderr);
		putc ('\n', stderr);
	}

	return 0;
}*/
