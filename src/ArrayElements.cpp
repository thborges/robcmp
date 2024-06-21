
#include "ArrayElements.h"

ArrayElements::ArrayElements(location_t loc): location(loc) {};

void ArrayElements::append(ArrayElement *e) {
	elements.push_back(e);
};

unsigned ArrayElements::getArraySize() {
	unsigned r = 0;
	for(auto& i : elements)
		r += i->count;
	return r;
};

unsigned ArrayElements::getStructSize() {
	return elements.size();
}

DataType ArrayElements::getArrayConstType(const set<DataType>& types, SourceLocation *location) {
	
	if (types.size() == 1) {
		// only one type
		return *types.begin();
	} else if (types.size() == 2) {
		// convert tchar and tint8 to tchar
		if (types.find(tchar) != types.end() && 
			types.find(tint8) != types.end())
			return tchar;
	}

	// int or float types: detect the largest
	DataType intdt, floatdt;
	unsigned largest_int = 0;
	unsigned largest_float = 0;
	for(auto dt : types) {
		unsigned bitw = buildTypes->bitWidth(dt);
		if (buildTypes->isIntegerDataType(dt) && largest_int < bitw) {
			largest_int = bitw;
			intdt = dt;
		}
		if (buildTypes->isFloatDataType(dt) && largest_float < bitw) {
			largest_float = bitw;
			floatdt = dt;
		}
	}

	if (largest_float > 0)
		return floatdt; // convert all to largest float
	else if (largest_int > 0)
		return intdt;   // convert all to largest int
	else {
		yyerrorcpp("Can't identify the array type based on its values.", location);
		return BuildTypes::undefinedType;
	}
}

DataType ArrayElements::getArrayType() {
	// find distinct types
	set<DataType> types;
	for(auto& i : elements) {
		DataType edt = i->value->getDataType();
		if (buildTypes->isEnum(edt))
			edt = tint8;
		types.emplace(edt);
	}
	return getArrayConstType(types, &location);
}

Node *ArrayElements::getStructElement(int position) {
	return elements[position]->value;
}

unsigned ArrayElements::getElementCount(int position) {
	return elements[position]->count;
}
