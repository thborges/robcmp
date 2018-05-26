//Program for Decimal to Roman Number conversion

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

extern float CoordX,CoordY,CoordZ;


/*Node* operacao(int num, int op){
	if(op==1){
		st->append(new Stmts(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(num)))));
	}
	if(op==2){
		st->append(new Stmts(new Variable("x",new BinaryOp(new Load("x"),'-',new Float(num)))));	
	}

return st;
}*/

Node* M();
Node* X();
Node* V();
Node* I();
Node* L();
Node* V();
Node* C();

Node* conta(Node* node,int a){
	Node* div = new BinaryOp(node,'/',new Int16(a));
	Node* r = new BinaryOp(div,'/',new Int16(10));
	Node* e = new BinaryOp(r,'*',new Int16(10));
	return new BinaryOp(div,'-',e);
}

Node* desenha(char num[]){
	Stmts* stmt;  //new Stmts(new LinearMove(new Float(CoordX),new Float(CoordY),new Float(1)));
	for(int i=0;i<strlen(num);i++){
		if(num[i]=='M'){
			if(i==0)
				 stmt =  new Stmts(M());
			else
				stmt->append(M());
			//CoordX+=1;
			stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
			stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
		}

		if(num[i]=='L'){
			if(i==0)
				 stmt =  new Stmts(L());
			else
				stmt->append(L());
			//CoordX+=1;	
			stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
			stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));

		}

		if(num[i]=='X'){
			if(i==0)
				 stmt =  new Stmts(X());
			
			else
				stmt->append(X());
			//CoordX+=1;	
			stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
			stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
		}

		if(num[i]=='I'){
			if(i==0)	
				 stmt =  new Stmts(I());
			else
				stmt->append(I());
			//CoordX+=1;	
			stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
			stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
		}
		if(num[i]=='V'){
			if(i==0)
				stmt = new Stmts(V());
			else
				stmt->append(V());
			stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
			stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
		}
		if(num[i]=='C'){
			if(i==0)
				stmt = new Stmts(C());
			else
				stmt->append(C());
			stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
			stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
			
		}
	}
	return stmt; 
}

Node* I(){
	
	Stmts* stmt = new Stmts(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	//CoordX+=1;
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
	CoordY+=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1.0)));
	return stmt;
}

Node* C(){
	Stmts* stmt = new Stmts(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(2.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Float(2.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(2.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	return stmt;
}

Node* V(){
	Stmts* stmt = new Stmts(new LinearMove(new Load("x"),new Float(CoordY),new Float(1.0)));
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
	CoordY-=3;
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Float(1.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=3;
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=3;
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
	return stmt;	
}

Node* X(){
	Stmts* stmt = new Stmts(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=3;
	//CoordX+=3;	
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(3.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	//CoordX-=3;
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'-',new Float(3.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(1)));
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=3;
	//CoordX+=3;	
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(3.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	return stmt;	
}

Node* L(){	
	Stmts* stmt = new Stmts(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(2.0))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	return stmt;
}


Node* M(){
	//CoordY-=3;
	Stmts* stmt = new Stmts(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=2; 
	//CoordX+=1.5;	
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.5))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY-=2;
	//CoordX+=1.5;
	stmt->append(new Variable("x",new BinaryOp(new Load("x"),'+',new Float(1.5))));	
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));
	CoordY+=3;
	stmt->append(new LinearMove(new Load("x"),new Float(CoordY),new Float(CoordZ)));	
	return stmt;
}


Node* decimalToarabic(Node* node){


Stmts* stmt = new Stmts(node);

stmt->append(new Variable("x",new Float(CoordX)));
 
stmt->append(new If(new CmpOp(node, GT_OP, new Int16(3999)), new Print(new Int16(-1)), NULL));

stmt->append(new If(new CmpOp(new BinaryOp(node, '/', new Int16(1000)), EQ_OP,new Int16(1)),desenha("M"),NULL));
stmt->append(new If(new CmpOp(new BinaryOp(node, '/', new Int16(1000)), EQ_OP,new Int16(2)),desenha("MM"),NULL));
stmt->append(new If(new CmpOp(new BinaryOp(node, '/', new Int16(1000)), EQ_OP,new Int16(3)),desenha("MMM"),NULL));

stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(1)),desenha("C"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(2)),desenha("CC"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(3)),desenha("CCC"),NULL));
/*stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(4)),desenha("CD"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(5)),desenha("D"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(6)),desenha("DC"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(7)),desenha("DCC"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(7)),desenha("DCC"),NULL));
stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(8)),desenha("DCCC"),NULL));
*/stmt->append(new If(new CmpOp(conta(node,100), EQ_OP,new Int16(9)),desenha("MC"),NULL));

stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(1)),desenha("X"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(2)),desenha("XX"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(3)),desenha("XXX"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(4)),desenha("XL"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(5)),desenha("L"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(6)),desenha("LX"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(7)),desenha("LXX"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(8)),desenha("LXXX"),NULL));
stmt->append(new If(new CmpOp(conta(node,10), EQ_OP,new Int16(9)),desenha("XC"),NULL));



stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(1)),desenha("I"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(2)),desenha("II"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(3)),desenha("III"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(4)),desenha("IV"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(5)),desenha("V"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(6)),desenha("VI"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(7)),desenha("VII"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(8)),desenha("VIII"),NULL));
stmt->append(new If(new CmpOp(conta(node,1), EQ_OP,new Int16(9)),desenha("IX"),NULL));

CoordX=1;CoordY+=4;CoordZ=0; 
return stmt;
}
