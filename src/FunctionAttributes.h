
#pragma once

enum FunctionAttributeType {
	fa_weak, 
	fa_inline, 
	fa_noinline, 
	fa_section, 
	fa_naked,
	fa_signal,
	fa_debugonly,
};

typedef pair<FunctionAttributeType, string> FunctionAttribute;

class FunctionAttributes {
protected:
	map<FunctionAttributeType, string> attributes;
public:
	FunctionAttributes() {}
	FunctionAttributes(FunctionAttributeType attr, const string& value = "") {
		addAttribute(attr, value);
	}
	void addAttribute(FunctionAttributeType attr, const string& value = "") {
		attributes[attr] = value;
	}
	void addAttribute(FunctionAttribute *attr) {
		attributes[attr->first] = attr->second;
		delete attr;
	}
	const map<FunctionAttributeType, string>& getAttributes() {
		return attributes;
	}
	bool hasAttribute(FunctionAttributeType attr) {
		return attributes.find(attr) != attributes.end();
	}
};
