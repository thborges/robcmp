
%name-prefix="MAIN"
//%define api.prefix {MAIN} // not working in Bison 3.8.2
%define parse.error verbose

%code provides {
  #define YY_DECL int MAINlex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
}

%type <node> term term2 expr factor stmt gstmt condblock whileblock logicexpr
%type <node> logicterm logicfactor TOK_AND TOK_OR printstmt fe eventblock unary
%type <node> funcblock func_decl func_impl returnblock registerstmt
%type <node> interfacestmt typestmt attribution enum_item enum
%type <strings> typestmt_impls
%type <ae> element
%type <aes> elements relements
%type <fp> funcparam
%type <fps> funcparams
%type <pc> paramscall
%type <me> melement
%type <mes> matrix
%type <nodes> stmts gstmts elseblock
%type <port> TOK_OUT TOK_IN
%type <nint> TOK_INTEGER qualifier
%type <nfloat> TOK_FLOAT
%type <ndouble> TOK_DOUBLE
%type <nldouble> TOK_LDOUBLE
%type <ident> TOK_IDENTIFIER TOK_XIDENTIFIER ident_or_xident
%type <str> TOK_STRING asminline
%type <nint> TOK_STEPPER
%type <str> error
%type <nodes> intf_decls enum_items

%%

programa : gstmts { 
	for(auto stmt : *($gstmts)) {
		program->addChild(stmt);
	}

	/*std::fstream fs;
	fs.open("ast", std::fstream::out);
	PrintAstVisitor(fs).visit(p);
	fs.close();*/

	if (errorsfound == 0)
		program->generate(); 
};

gstmts : gstmts gstmt {
	if ($gstmt) { // TOK_USE returns NULL
		$1->push_back($gstmt);
	}
}

gstmts : gstmt {
	$$ = new vector<Node*>();
	if ($gstmt) {
		$$->push_back($gstmt);
		$gstmt->setLocation(@gstmt);
	}
}

gstmt : TOK_USE TOK_IDENTIFIER ';' 					{ parseUseFile($2, @TOK_USE); $$ = NULL; }
	  | attribution ';'								{ $$ = $1; }
	  | qualifier attribution ';'					{ $$ = $2; $$->setQualifier((DataQualifier)$1); }
	  | registerstmt								{ $$ = $1; }
	  | interfacestmt								{ $$ = $1; }
	  | typestmt									{ $$ = $1; }
	  | fe											{ $$ = $1; }
	  | enum                                        { $$ = $1; }
	  | error ';'									{ /* error recovery until next ';' */
													  $$ = new Int8(0); // evita falha de segmentacao
													};


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

attribution : ident_or_xident[id] '=' expr {
	$$ = new Scalar($id, $expr);
	$$->setLocation(@id);
}

attribution : ident_or_xident[id] '=' '{' elements '}' {
	$$ = new Array($id, $elements);
	$$->setLocation(@id);
}

attribution : ident_or_xident[id] '=' '{' matrix '}' {
	$$ = new Matrix($id, $matrix);
	$$->setLocation(@id);
}

qualifier : TOK_CONST		{ $$ = qconst; }
		  | TOK_VOLATILE	{ $$ = qvolatile; }

fe : funcblock	{ $$ = $1; } 
   | eventblock	{ $$ = $1; } 
   ;

funcblock : func_decl | func_impl ;

func_decl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' funcparams ')' ';' {
				$$ = new FunctionDecl(buildTypes->getType($type, true), $id, $funcparams);
				$$->setLocation(@type);
			}
func_impl : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] '(' funcparams ')' '{' stmts '}'[ef] {
				$$ = new FunctionImpl(buildTypes->getType($type, true), $id, $funcparams,
						std::move(*$stmts), @ef); 
				$$->setLocation(@type);
			}
		  ;

eventblock : TOK_QUANDO TOK_INTEGER TOK_ESTA TOK_INTEGER '{' stmts '}'[ef] {	
				/*char funcname[100];
				snprintf(funcname, 100, "__callback_int_p%d_e%d", (int)$2, (int)$4);
				vectorglobal.push_back(new AttachInterrupt($2, funcname, $4));
				FunctionParams *fps = new FunctionParams();
				$$ = new FunctionImpl(tvoid, funcname, fps, $6, @ef);*/
				return 0;
             }
		   ;

stmts : stmts stmt {
	$1->push_back($stmt);
}

stmts : stmt {
	$$ = new vector<Node*>();
	$$->push_back($stmt);
	$stmt->setLocation(@stmt);
}

stmt : gstmt									{ $$ = $1; }
	 | TOK_OUT '=' expr ';'						{ $$ = new OutPort($1, $3); } 
	 | ident_or_xident[id] '(' paramscall ')' ';'	{ $$ = new FunctionCall($id, $3); $$->setLocation(@id);}
	 | TOK_IDENTIFIER '+' '+' ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', new Int8(1))); }
	 | TOK_IDENTIFIER '-' '-' ';'				{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', new Int8(1))); }
	 | TOK_IDENTIFIER '+' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '+', $4)); }
	 | TOK_IDENTIFIER '-' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '-', $4)); }
	 | TOK_IDENTIFIER '*' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '*', $4)); }
	 | TOK_IDENTIFIER '/' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '/', $4)); }
	 | TOK_IDENTIFIER '|' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '|', $4)); }
	 | TOK_IDENTIFIER '&' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '&', $4)); }
	 | TOK_IDENTIFIER '^' '=' expr ';'			{ $$ = new Scalar($1, new BinaryOp(new Load($1), '^', $4)); }
	 | TOK_DELAY expr';'						{ $$ = new Delay($2); }
	 | condblock								{ $$ = $1; }
	 | whileblock								{ $$ = $1; }
	 | returnblock ';'							{ $$ = $1; }
	 | printstmt ';'							{ $$ = $1; }
	 | asminline ';'							{ $$ = new InlineAssembly($1); $$->setLocation(@1); }
	 | TOK_IDENTIFIER '[' expr ']' '=' expr ';'	{ $$ = new UpdateArray($1, $3, $6);}
	 | TOK_IDENTIFIER '[' expr ']' '[' expr ']' '=' expr ';'	{ $$ = new UpdateMatrix($1, $3, $6, $9); }


matrix : matrix ',' melement			{ $1->append($3);
										  $$ = $1; }
	   | melement						{ MatrixElements *mes = new MatrixElements();
										  mes->append($1);
										  $$ = mes; }
	   ;


melement : relements ':' TOK_INTEGER	{ $$ = new MatrixElement($1, (unsigned)$3); }
	     | relements					{ $$ = new MatrixElement($1, 1);}
	     ;
	 
relements : '{' elements '}'			{ $$ = $2; }
		  ;

elements : elements ',' element			{ $1->append($3);
										  $$ = $1; }
		 | element						{ ArrayElements *aes = new ArrayElements();
										  aes->append($1);
										  $$ = aes; }
		 ;

element : factor ':' TOK_INTEGER		{ $$ = new ArrayElement($1, (unsigned)$3); }
        | factor						{ $$ = new ArrayElement($1, 1); }
	    ;

funcparams: funcparams ',' funcparam {
				$1 -> append($3);
				$$ = $1; 
			}
	      | funcparam {
				FunctionParams *fps = new FunctionParams();
				fps->append($1);
				$$ = fps; 
			}
		  | %empty {
				FunctionParams *fps = new FunctionParams();
				$$ = fps;
			}
		  ;

funcparam : TOK_IDENTIFIER[type] TOK_IDENTIFIER[id] {
				$$ = new FunctionParam($id, buildTypes->getType($type, true));
			}

paramscall : paramscall ',' expr {$1 -> append($3);
								  $$ = $1;}
		   | expr { ParamsCall *pc = new ParamsCall();
		            pc->append($1);
				    $$ = pc;}
		   | %empty { ParamsCall *pc = new ParamsCall();
			   $$ = pc;
			 }
		   ;

returnblock : TOK_RETURN expr			{ $$ = new Return($2); }
			| TOK_RETURN logicexpr		{ $$ = new Return($2); }
			| TOK_RETURN				{ $$ = new Return(); }
			;

condblock : TOK_IF logicexpr '{' stmts '}' {
			  $logicexpr->setLocation(@logicexpr);
			  $$ = new If($logicexpr, std::move(*$stmts));
			  $$->setLocation(@TOK_IF);
			}
		  | TOK_IF logicexpr '{' stmts '}' elseblock {
			  $logicexpr->setLocation(@logicexpr);
			  $$ = new If($logicexpr, std::move(*$stmts), std::move(*$elseblock));
			  $$->setLocation(@TOK_IF);
			}
		  ;

elseblock : TOK_ELSE '{' stmts '}' { $$ = $stmts; }

whileblock : TOK_WHILE logicexpr '{' stmts '}' {
			   $logicexpr->setLocation(@logicexpr);
			   $$ = new While($logicexpr, std::move(*$stmts));
			   $$->setLocation(@TOK_WHILE);
			 }
		   | TOK_WHILE logicexpr ';' {
			   $logicexpr->setLocation(@logicexpr);
			   $$ = new While($logicexpr);
			   $$->setLocation(@TOK_WHILE);
		     }
		   | TOK_LOOP '{' stmts '}' {
		       $$ = new Loop(std::move(*$stmts));
			   $$->setLocation(@TOK_LOOP);
			 }
		   ;

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
	   | TOK_IDENTIFIER '[' expr ']'				{ $$ = new LoadArray($1, $3);} 
	   | TOK_IDENTIFIER '[' expr ']' '[' expr ']'	{ $$ = new LoadMatrix($1, $3, $6);}
	   | TOK_TRUE				{ $$ = new Int1(1); }
	   | TOK_FALSE				{ $$ = new Int1(0); }
	   | TOK_INTEGER			{ $$ = getNodeForIntConst($1); }
	   | TOK_FLOAT				{ $$ = new Float($1); }
	   | TOK_DOUBLE				{ $$ = new Double($1); }
	   | TOK_LDOUBLE			{ $$ = new Float128($1); }
	   | TOK_IN					{ $$ = new InPort($1); }
	   | ident_or_xident[id] '(' paramscall ')'	{ $$ = new FunctionCall($id, $paramscall); $$->setLocation(@id); }
	   | unary { $$ = $1; }
	   ;

ident_or_xident: TOK_IDENTIFIER | TOK_XIDENTIFIER

unary : '-' factor	{ $$ = new BinaryOp($2, '*', getNodeForIntConst(-1)); }
	  | '~' factor	{ $$ = new FlipOp($2); }
      ;

printstmt : TOK_PRINT TOK_STRING		{ $$ = new Print(new StringConst($2)); }
		  | TOK_PRINT expr				{ $$ = new Print($2); }

registerstmt : TOK_REGISTER TOK_IDENTIFIER[type] TOK_IDENTIFIER[name] TOK_AT expr ';' {
	$$ = new Pointer($name, buildTypes->getType($type, true), $5);
	$$->setQualifier(qvolatile);
	$$->setLocation(@name);
}

asminline : TOK_ASM TOK_STRING { $$ = $2; }
		  ;

interfacestmt : TOK_INTF TOK_IDENTIFIER '{' intf_decls '}' {
	$$ = new Interface($TOK_IDENTIFIER, std::move(*$intf_decls));
	$$->setLocation(@TOK_INTF);
};

interfacestmt : TOK_INTF TOK_IDENTIFIER '{' '}' {
	$$ = new Interface($TOK_IDENTIFIER);
	$$->setLocation(@TOK_INTF);
};

intf_decls : intf_decls func_decl {
	$1->push_back($func_decl);
	$$ = $1;
};

intf_decls : func_decl {
	$$ = new vector<Node*>();
	$$->push_back($func_decl);
};

typestmt : TOK_TYPE TOK_IDENTIFIER TOK_IMPL typestmt_impls '{' stmts '}' {
	$$ = new UserType($TOK_IDENTIFIER, std::move(*$stmts), std::move(*$typestmt_impls));
	$$->setLocation(@TOK_TYPE);
}

typestmt : TOK_TYPE TOK_IDENTIFIER '{' stmts '}' {
	$$ = new UserType($TOK_IDENTIFIER, std::move(*$stmts));
	$$->setLocation(@TOK_TYPE);
}

typestmt_impls : typestmt_impls ',' TOK_IDENTIFIER {
	$1->push_back($TOK_IDENTIFIER);
	$$ = $1;
}

typestmt_impls : TOK_IDENTIFIER {
	$$ = new vector<string>();
	$$->push_back($1);
}

%%
