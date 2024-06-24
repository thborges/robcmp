
#pragma once

enum FunctionAttributeType {fa_weak, fa_inline, fa_noinline, fa_section, fa_naked};

typedef pair<FunctionAttributeType, string> FunctionAttribute;

class FunctionAttributes {
protected:
	vector<FunctionAttribute*> attributes;
public:
	FunctionAttributes() {}
	FunctionAttributes(FunctionAttributeType attr, const string& value = "") {
		addAttribute(attr, value);
	}
	~FunctionAttributes() {
		for(auto *attr : attributes)
			delete attr;
	}
	void addAttribute(FunctionAttributeType attr, const string& value = "") {
		attributes.push_back(new FunctionAttribute(attr, value));
	}
	void addAttribute(FunctionAttribute *attr) {
		attributes.push_back(attr);
	}
	const vector<FunctionAttribute*>& getAttributes() {
		return attributes;
	}
};
