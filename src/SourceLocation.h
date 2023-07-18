
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
};
