
%name-prefix="USE"
//%define api.prefix {USE} // not working in Bison 3.8.2
%define parse.error verbose
//%define parse.trace

%code provides {
  #define YY_DECL int USElex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
  //#define YYDEBUG 1
}

%type<nodes> gstmts
%type<node> gstmt register interface type ignores ignore_once ignore use
%type<node> function function_decl function_impl var_decl
%type<fps> function_params
%type<fp> function_param
%type<nodes> intf_decls
%type<node> const_expr
%type<ident> TOK_IDENTIFIER
%type<nint> TOK_INTEGER
%type<structure> struct_fields
%type<field> struct_field
%type<strings> type_impls
%type<str> error;

%%

programa : gstmts {
	for(auto stmt : *($gstmts)) {
		program->addChild(stmt);
	}
}

gstmts : gstmts gstmt {
	$1->push_back($gstmt);
	//$gstmt->setScope(program);
}

gstmts : gstmt {
	$$ = new vector<Node*>();
	if ($gstmt) {
		$$->push_back($gstmt);
		//$gstmt->setScope(program);
		$gstmt->setLocation(@gstmt);
	}
}

gstmt : register
	  | interface
	  | type
	  | function
	  | var_decl
      | ignore_once
	  | use

use : TOK_USE TOK_IDENTIFIER ';' {
	parseUseFile($2, @TOK_USE);
	$$ = NULL;
}

function : function_decl | function_impl

function_decl : TOK_IDENTIFIER[type] TOK_IDENTIFIER '(' function_params ')' ';' {
    $$ = new FunctionDecl(buildTypes->getType($type, true), $2, $4);
    $$->setLocation(@type);
}

function_impl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' function_params ')' '{' ignores '}'[ef] {
	vector<Node*> auxvec;
	$$ = new FunctionImpl(buildTypes->getType($type, true), $id, $function_params,
			std::move(auxvec), @ef); 
    $$->setLocation(@type);
}

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

register : TOK_REGISTER TOK_IDENTIFIER[type] TOK_IDENTIFIER[name] TOK_AT const_expr ';' {
	$$ = new Pointer($name, buildTypes->getType($type, true), $5);
	$$->setQualifier(qvolatile);
	$$->setLocation(@name);
}

register : TOK_REGISTER TOK_IDENTIFIER[type] TOK_IDENTIFIER[name] TOK_AT const_expr '{' struct_fields '}' {
	$$ = new Pointer($name, buildTypes->getType($type, true), $5, $7);
	$$->setLocation(@name);
}

struct_fields : struct_fields struct_field {
				  $2->startBit = $1->nextBit;
	              $1->fields[$2->getName()] = $2;
				  $1->nextBit += $2->bitWidth;
				  $$ = $1;
				}
              | struct_field {
			      Structure *s = new Structure();
				  $1->startBit = 0;
				  s->fields[$1->getName()] = $1;
				  s->nextBit = $1->bitWidth;
				  $$ = s;
				}
			  ;

struct_field : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] ';' {
				 Field *s = new Field($id, buildTypes->getType($type, true));
				 s->bitWidth = buildTypes->bitWidth(s->getDataType());
				 $$ = s;
			   }
			 | TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] ':' TOK_INTEGER[bit] ';' {
				 Field *s = new Field($id, buildTypes->getType($type, true));
				 s->bitWidth = (unsigned)$bit;
				 $$ = s;
			   }

interface : TOK_INTF TOK_IDENTIFIER '{' intf_decls '}' {
	$$ = new Interface($TOK_IDENTIFIER, std::move(*$intf_decls));
	$$->setLocation(@TOK_INTF);
}

interface : TOK_INTF TOK_IDENTIFIER '{' '}' {
	$$ = new Interface($TOK_IDENTIFIER);
	$$->setLocation(@TOK_INTF);
}

intf_decls : intf_decls function_decl {
	$1->push_back($function_decl);
	$$ = $1;
}

intf_decls : function_decl {
	$$ = new vector<Node*>();
	$$->push_back($function_decl);
}

type : TOK_TYPE TOK_IDENTIFIER TOK_IMPL type_impls '{' gstmts '}' {
	$$ = new UserType($TOK_IDENTIFIER, std::move(*$gstmts), std::move(*$type_impls));
	$$->setLocation(@TOK_TYPE);
}

type : TOK_TYPE TOK_IDENTIFIER '{' gstmts '}' {
	$$ = new UserType($TOK_IDENTIFIER, std::move(*$gstmts));
	$$->setLocation(@TOK_TYPE);
}

type_impls : type_impls ',' TOK_IDENTIFIER {
	$1->push_back($TOK_IDENTIFIER);
	$$ = $1;
}

type_impls : TOK_IDENTIFIER {
	$$ = new vector<string>();
	$$->push_back($1);
}

var_decl : TOK_IDENTIFIER '=' const_expr ';' { $$ = new Scalar($1, $3); };

const_expr : TOK_INTEGER    { $$ = getNodeForIntConst($1); }

ignores : ignores ignore_once
        | ignore_once

ignore_once : ignore ';'	{ $$ = NULL; }
		    | error ';'		{ $$ = NULL; }
			| error '}'		{ $$ = NULL; }

/* put here any symbol that can start a stmt (except globals)
 * to be precise, the FIRST(stmt)
 */
ignore : TOK_IDENTIFIER { YYERROR; }
	   | TOK_WHILE      { YYERROR; }
	   | TOK_RETURN     { YYERROR; }
	   | TOK_CONST      { YYERROR; }
	   | TOK_VOLATILE   { YYERROR; }
	   | TOK_IF         { YYERROR; }
	   | TOK_LOOP       { YYERROR; }
	   | TOK_ASM        { YYERROR; }
	   | TOK_PRINT      { YYERROR; }
	   | TOK_DELAY      { YYERROR; }

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
