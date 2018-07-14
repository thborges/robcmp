
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

void onexit(void) __attribute__ ((destructor));

#define ARDUINO_PORTS 14
int arduino_out_ports[ARDUINO_PORTS];
int steppers_pos[3] = {0};

#define LCD_ROWS 6
#define LCD_COLS 14
#define LCD_CHARS (LCD_ROWS*LCD_COLS)
char display[LCD_CHARS];
int display_pos = 0;
char last_msg[1000];

char *port_names[ARDUINO_PORTS] = {
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
};

void refresh_screen() {

	mvprintw(1, 1, "Simulador de E/S para Robcmp");
	mvprintw(2, 1, "----------------------------");

	mvprintw(6, 1, "Ultima msg: ");
	attron(COLOR_PAIR(3));
	mvprintw(6, 14, "%s                                     ", last_msg);
	attroff(COLOR_PAIR(3));

	int currow = 10;
	mvprintw(currow++, 1, "[ Mensagens print ]");
	mvprintw(currow++, 1, "---------------");
	attron(COLOR_PAIR(2));
	for(int r=0; r<LCD_ROWS; r++) {
		char aux[LCD_COLS+1];
		strncpy(aux, &display[r*LCD_COLS], LCD_COLS);
		aux[LCD_COLS] = '\0';
		mvprintw(currow++, 1, "%s", aux);
	}
	attroff(COLOR_PAIR(2));
	mvprintw(currow++, 1, "---------------");
	
	currow += 5;
	mvprintw(currow++, 1, "Status portas");
	mvprintw(currow++, 1, "--------------");
	attron(COLOR_PAIR(2));
	for(int i = 0; i < ARDUINO_PORTS; i++)
		mvprintw(currow++, 1, "[%4d] %s", arduino_out_ports[i], port_names[i]);
	attroff(COLOR_PAIR(2));
	mvprintw(currow++, 1, "--------------");

	refresh();
}

void init() {
	initscr();
	cbreak();
	//noecho();
	keypad(stdscr, TRUE);
	start_color();
	last_msg[0] = 0;

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_WHITE);

	memset(arduino_out_ports, 0, sizeof arduino_out_ports);
	memset(display, 0, sizeof display);

	refresh_screen();
};

void print(char t, void *data) {
	char buff[1024];

	switch (t) {
		case 0: sprintf(buff, "%d\n", *(short*)data); break;
		case 1: sprintf(buff, "%f\n", *(float*)data); break;
		case 2: sprintf(buff, "%s\n", (char*)data); break;
	}

	for(int i=0; i < strlen(buff); i++) {
		display[display_pos] = buff[i] == '\n' ? ' ' : buff[i];
		display_pos = (display_pos + 1) % LCD_CHARS;	
	}

	refresh_screen();
}

int analogRead(unsigned char t) {
	int a;

	attron(COLOR_PAIR(3));
	mvprintw(5, 1, "Digite valor para porta A%d: __________", t);
	mvscanw(5, 29, "%d", &a);
	attroff(COLOR_PAIR(3));

	refresh_screen();
	return a;

}

//void digitalWrite(char port, char value) {
void analogWrite(char port, short value) {

	if (port > ARDUINO_PORTS) {
		attron(COLOR_PAIR(3));
		sprintf(last_msg, "Erro: porta %d nao existe.",
			port);
		attroff(COLOR_PAIR(3));
	} else {
		arduino_out_ports[port] = value;
	}

	refresh_screen();
}

void delay(int milis) {
	attron(COLOR_PAIR(3));
	sprintf(last_msg, "Delay %d milis", milis);
	attroff(COLOR_PAIR(3));
	refresh_screen();
	
	usleep(milis*1000);
}

void stepper_goto(int stepper, int pos) {
	attron(COLOR_PAIR(3));
	sprintf(last_msg, "Motor %d move para posicao %d.", stepper, pos);
	attroff(COLOR_PAIR(3));
	refresh_screen();
	usleep(1e6);
}

void servo_goto(int pos) {
	attron(COLOR_PAIR(3));
	if (pos >= 0 && pos <= 30) {
		sprintf(last_msg, "Servo move para posicao %d.", pos);
	} else {
		sprintf(last_msg, "Servo nao pode se mover para posicao %d (0-30).", pos);
	}
	attroff(COLOR_PAIR(3));
	refresh_screen();
	usleep(1e6);
}

void onexit(void) {
	getchar();
    curs_set(1);
    clear();
    endwin();
}

/*int main() {

	int r = 10;
	float d = 100.903;

	print(1, &d);
	print(0, &r);
}
*/
