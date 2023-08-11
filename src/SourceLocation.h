
#pragma once

#include "HeaderExternals.h"

typedef struct {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} location_t;

extern const filesystem::path* build_file();
extern int build_filecolno();
extern int build_filelineno();

class SourceLocation {
protected:
	location_t sloc;
	const filesystem::path *file;
public:
    SourceLocation() {
        file = build_file();
		sloc.first_column = build_filecolno();
		sloc.first_line = build_filelineno();
    }

    SourceLocation(location_t l): SourceLocation() {
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

	virtual location_t *getLoct() {
		return &sloc;
	}

	virtual const string getFile() const {
		return file->string();
	}
};
