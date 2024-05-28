#pragma once

#include "BuildTypes.h"
#include "Node.h"
#include "FunctionParams.h"
#include "Variable.h"
#include "Matrix.h"

class FunctionBase: public NamedNode {
protected:
	FunctionParams *parameters;
	Function *func = NULL;
	bool declaration = true;
	bool constructor = false;
	bool external = false;
	DataType thisArgDt = BuildTypes::undefinedType;
	string prefixName;

	bool validateAndGetArgsTypes(std::vector<Type*> &args);

public:
	FunctionBase(DataType dt, string name, FunctionParams *fp) : NamedNode(name) {
		this->dt = dt;
		this->parameters = fp;
		addPseudoParameters();
	}

	FunctionBase(DataType dt, string name, FunctionParams *fp, vector<Node*> &&stmts,
		bool constructor = false) :
		NamedNode(name, std::move(stmts)) {
		this->dt = dt;
		this->parameters = fp;
		this->constructor = constructor;
		addPseudoParameters();
	}

	void addPseudoParameters() {
        // add a size parameter after each array, or .rows and .cols for matrixes
		std::vector<Variable*> const& vparams = this->parameters->getParameters();
		for (int i = 0; i < vparams.size(); ++i) {
			Variable *p = vparams[i];

			DataType pdt = p->getDataType();
	        if (buildTypes->isArrayOrMatrix(pdt)) {
				vector<string> pseudos;
				if (buildTypes->isArray(pdt))
					pseudos.push_back("size");
				else if (buildTypes->isMatrix(pdt)) {
					// let it inverted here, because of the insert below (i+1)
					pseudos.push_back("cols");
					pseudos.push_back("rows");
				}

            	for(const string& s: pseudos) {
					//TODO: There is something better than fix this to Int32? Fix here and in FunctionCall::generate
					string spname = p->getName() + "." + s;
					Variable *sp = new Variable(spname, tint32); 
					this->parameters->insert(i+1, sp);

					// add a pseudo symbol to resolve to pname.s
					p->addSymbol(s, sp);
				}

				// ParamMatrix need to know the number of cols to compute element indexes
				if (buildTypes->isMatrix(pdt)) {
					if (ParamMatrix *pm = dynamic_cast<ParamMatrix*>(p))
						pm->setCols(vparams[i+2]);
				}
			}
		}
	}

	FunctionParams& getParameters() {
		return *parameters;
	}

	virtual Value *getLLVMValue(Node *) override {
		return func;
	}

	virtual Function *getLLVMFunction() {
		return func;
	}

	unsigned getNumCodedParams() const {
		return parameters->getNumCodedParams();
	}

	bool isDeclaration() {
		return declaration;
	}

	bool isConstructor() {
		return constructor;
	}

	void setExternal(bool e) {
		external = e;
	}

	bool isExternal() {
		return external;
	}

	void addThisArgument(DataType dt);
	
	DataType getThisArgDt() const {
		return thisArgDt;
	}

	void setPrefixName(const string& prefix) {
		prefixName = prefix;
	}

	string getFinalName() {
		if (prefixName == "")
			return name;
		else
			return prefixName + ":" + name;
	}

	virtual bool needsParent() {
		return false;
	}
};

class FunctionDecl: public FunctionBase {
public:
	FunctionDecl(DataType dt, string name, FunctionParams *fp) : 
		FunctionBase(dt, name, fp) {
		declaration = true;
	}

	virtual Value *generate(FunctionImpl *func, BasicBlock *block, BasicBlock *allocblock) override;
};
