
Int16* liga = new Int16(255);
Int16* desliga = new Int16(0);

Int16* delayMeio = new Int16(500);
Int16* delayMeio1 = new Int16(700);
Int16* delayCompleto = new Int16(1000);
Int16* delayProximo = new Int16(4000);


While *AGUARDE(){
		CmpOp *comp = new CmpOp(new InPort("2"), EQ_OP, new Int16(0));
		Stmts *delay = new Stmts(new Delay(new Int16(10)));
		While *w = new While(comp, delay);
		return w;
}

Stmts *RETANGULO() {
		Stmts *comms = new Stmts(new OutPort("2", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("2", desliga));
								comms->append(new OutPort("4",liga));
								comms->append(new Delay(delayMeio1));
								comms->append(new OutPort("7", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("4",desliga));
								comms->append(new OutPort("7", desliga));
								comms->append(new OutPort("3", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("3", desliga));
								comms->append(new OutPort("5", liga));
								comms->append(new OutPort("6", liga));
								comms->append(new Delay(delayMeio));
								comms->append(new Delay(delayMeio));
								comms->append(new OutPort("5", desliga));
								comms->append(new OutPort("6",desliga));
return comms;
}

Stmts *UFG() {
Stmts *comms = new Stmts(new OutPort("2", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("2", desliga));
								comms->append(new OutPort("4",liga));
								comms->append(new Delay(delayMeio1));
								comms->append(new OutPort("7", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("4",desliga));
								comms->append(new OutPort("7", desliga));
								comms->append(new OutPort("3", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("3", desliga));
								comms->append(new Delay(delayProximo));
								comms->append(new OutPort("5", liga));
								comms->append(new OutPort("6", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("5", desliga));
								comms->append(new OutPort("6",desliga));
								comms->append(new OutPort("2", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("2",desliga));
								comms->append(new OutPort("3", liga));
								comms->append(new Delay(delayMeio1));
								comms->append(new OutPort("3",desliga));
								comms->append(new OutPort("4",liga));
								comms->append(new OutPort("7", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("4",desliga));
								comms->append(new OutPort("7", desliga));
								comms->append(new Delay(delayProximo));
								comms->append(new OutPort("5", liga));
								comms->append(new OutPort("6", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("5", desliga));
								comms->append(new OutPort("6",desliga));
								comms->append(new OutPort("2", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("2",desliga));
								comms->append(new OutPort("3", liga));
								comms->append(new Delay(delayMeio1));
								comms->append(new OutPort("3",desliga));
								comms->append(new OutPort("4",liga));
								comms->append(new OutPort("7", liga));
								comms->append(new Delay(delayCompleto));
								comms->append(new OutPort("4",desliga));
								comms->append(new OutPort("7", desliga));
								comms->append(new OutPort("2", liga));
								comms->append(new Delay(delayMeio1));
								comms->append(new OutPort("2",desliga));
								comms->append(new OutPort("5",liga));
								comms->append(new OutPort("6", liga));
								comms->append(new Delay(delayMeio1));
								comms->append(new OutPort("5",desliga));
								comms->append(new OutPort("6", desliga));
	comms->append(new OutPort("5", desliga));
	return comms;
}
