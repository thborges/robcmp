
#pragma once

#include "HeaderExternals.h"

typedef struct {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} location_t;

extern int buildStackCurrent;
extern vector<filesystem::path> buildStack;

class SourceLocation {
protected:
	location_t sloc;
	int fileNo;
	bool semanticError = false;
	
public:
    SourceLocation(location_t l) {
        fileNo = buildStackCurrent;
        sloc = l;
    }

    virtual int getLineNo() const {
		return sloc.first_line;
	}

	virtual int getColNo() const {
		return sloc.first_column;
	}

	virtual void setLocation(location_t l) {
		sloc = l;
	}
	
	virtual void setLocation(SourceLocation *s) {
		sloc = s->sloc;
	}

	virtual location_t getLoc() {
		return sloc;
	}

	virtual const string getFile() const {
		return buildStack[fileNo];
	}

	bool hasSemanticError() const {
		return semanticError;
	}

	void setSemanticError() {
		semanticError = true;
	}
};
