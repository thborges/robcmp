
#pragma once

typedef struct {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} location_t;

class SourceLocation {
protected:
	location_t sloc;
public:
    SourceLocation() {
        //TODO: sloc = yylloc;
    }

    SourceLocation(location_t l) {
        sloc = l;
    }

    virtual int getLineNo() {
		return sloc.first_line;
	}

	virtual int getColNo() {
		return sloc.first_column;
	}

	virtual void setLocation(location_t l) {
		sloc = l;
	}
	
	virtual void setLocation(SourceLocation *s) {
		sloc = s->sloc;
	}

	virtual location_t *getLoct() {
		return &sloc;
	}
};
