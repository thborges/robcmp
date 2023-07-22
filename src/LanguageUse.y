
%name-prefix="USE"
//%define api.prefix {USE} // not working in Bison 3.8.2

%code provides {
  #define YY_DECL int USElex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t yyscanner)
  YY_DECL;
  void yyerror(YYLTYPE *yyloc, yyscan_t yyscanner, const char *msg);
}

%type<stmt> gstmts
%type<node> gstmt register interface type 
%type<node> function function_decl function_impl
%type<fps> function_params
%type<fp> function_param
%type<nodes> intf_decls
%type<node> const_expr
%type<ident> TOK_IDENTIFIER
%type<nint> TOK_INTEGER
%type<dt> type_f register_type
%type<structure> struct_fields
%type <field> struct_field
%type <strings> type_impls

%%

programa : gstmts
		 ;

gstmts : gstmts gstmt   { $1->append($gstmt);}
	   | gstmt          { $$ = new Stmts($gstmt); $gstmt->setLocation(@gstmt); }
	   ;

gstmt : register    {  }
	  | interface   {  }
	  | type        {  }
	  | function    {  }
      | ignore      {  }
      ;

function : function_decl | function_impl ;

function_decl : type_f TOK_IDENTIFIER '(' function_params ')' ';' {
    $$ = new FunctionDecl($1, $2, $4);
    $$->setLocation(@type_f);
};

function_impl : type_f TOK_IDENTIFIER '(' function_params ')' '{' gstmt '}'[ef] {
    $$ = new FunctionDecl($1, $2, $4);
    $$->setLocation(@type_f);
};

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

function_param : type_f TOK_IDENTIFIER[id] {
				$$ = FunctionParam{$id, $type_f};
			}
		  | TOK_IDENTIFIER[id1] TOK_IDENTIFIER[id2] { 
				$$ = FunctionParam{$2, tvoid};
		    }
		  ;

type_f  : TOK_VOID { $$ = tvoid; }
		| TOK_FCHAR { $$ = tchar; }
		| TOK_FBOOL { $$ = tbool; }
		| TOK_FINT8 { $$ = tint8; } 
		| TOK_FINT16 { $$ = tint16; } 
		| TOK_FINT32 { $$ = tint32; } 
		| TOK_FINT64 { $$ = tint64; } 
		| TOK_FUNSIGNED TOK_FINT8 { $$ = tint8u; } 
		| TOK_FUNSIGNED TOK_FINT16 { $$ = tint16u; } 
		| TOK_FUNSIGNED TOK_FINT32 { $$ = tint32u; } 
		| TOK_FUNSIGNED TOK_FINT64 { $$ = tint64u; } 
		| TOK_FFLOAT { $$ = tfloat; } 
		| TOK_FDOUBLE { $$ = tdouble; } 
		| TOK_FLONG TOK_FDOUBLE { $$ = tldouble; } 
/*		| TOK_IDENTIFIER[ident] {
			yyerrok;
			yyerrorcpp(string_format("Invalid type name '%s'.", $ident), nullptr);
			$$ = tvoid; 
		  }*/
	    ;

register : TOK_REGISTER register_type TOK_IDENTIFIER TOK_AT const_expr ';' {
				 $$ = new Pointer($3, $2, $5, true);
			   }
			 | TOK_REGISTER register_type TOK_IDENTIFIER TOK_AT const_expr '{' struct_fields '}' {
				 $$ = new Pointer($3, $2, $5, $7, true);
			   }
			 ;

register_type : TOK_FINT8	{ $$ = tint8; }
			  | TOK_FINT16	{ $$ = tint16; }
			  | TOK_FINT32	{ $$ = tint32; }
			  | TOK_FINT64	{ $$ = tint64; }
			  ;

struct_fields : struct_fields struct_field {
				  $2.startBit = $1->nextBit;
	              $1->fields[$2.fieldName] = $2;
				  $1->nextBit += $2.bitWidth;
				  $$ = $1;
				}
              | struct_field {
			      Structure *s = new Structure();
				  $1.startBit = 0;
				  s->fields[$1.fieldName] = $1;
				  s->nextBit = $1.bitWidth;
				  $$ = s;
				}
			  ;

struct_field : type_f TOK_IDENTIFIER ';' {
			     $$.fieldDataType = $1;
				 $$.fieldName = $2;
				 $$.bitWidth = buildTypes->bitWidth($1);
			   }
			 | type_f TOK_IDENTIFIER ':' TOK_INTEGER ';' {
			     $$.fieldDataType = $1;
				 $$.fieldName = $2;
				 $$.bitWidth = (unsigned)$4;
			   }
             ;

interface : TOK_INTF TOK_IDENTIFIER '{' intf_decls '}' {
	$$ = new Interface($TOK_IDENTIFIER, std::move(*$intf_decls));
	$$->setLocation(@TOK_INTF);
};

interface : TOK_INTF TOK_IDENTIFIER '{' '}' {
	$$ = new Interface($TOK_IDENTIFIER);
	$$->setLocation(@TOK_INTF);
};

intf_decls : intf_decls function_decl {
	$1->push_back($function_decl);
	$$ = $1;
};

intf_decls : function_decl {
	$$ = new vector<Node*>();
	$$->push_back($function_decl);
};

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

const_expr : TOK_INTEGER    { $$ = getNodeForIntConst($1); }

ignore : error { yyerrok; };

%%

