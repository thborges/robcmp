
#pragma once

extern int yylineno;
extern int yycolno;

class SourceLocation {
protected:
	int lineno;
	int colno;
public:
    SourceLocation() {
        lineno = yylineno;
        colno = yycolno;
    }

    SourceLocation(location_t l) {
        setLocation(l);
    }

    virtual int getLineNo() {
		return lineno;
	}

	virtual int getColNo() {
		return colno;
	}

	virtual void setLocation(location_t l) {
		lineno = l.first_line;
		colno = l.first_column;
	}
	
	virtual void setLocation(SourceLocation *s) {
		lineno = s->lineno;
		colno = s->colno;
	}
};
