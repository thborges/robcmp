
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define ARDUINO_PORTS 14
char arduino_out_ports[ARDUINO_PORTS];

#define LCD_ROWS 6
#define LCD_COLS 14
#define LCD_CHARS (LCD_ROWS*LCD_COLS)
char display[LCD_CHARS];
int display_pos = 0;

char *port_names[ARDUINO_PORTS] = {
	"LCD DC",
	"LCD Reset",
	"Motor 1 Horario",
	"Motor 1 Anti-horario",
	"Motor 2 Horario",
	"Motor 2 Anti-horario",
	"Motor 3 Horario",
	"Motor 3 Anti-horario",
	"Motor 4 Horario",
	"Motor 4 Anti-horario",
	"Motor 5 Horario",
	"LCD MOSI",
	"Motor 5 Anti-horario",
	"LCD SCK",
};

void refresh_screen() {

	mvprintw(1, 1, "Simulador de E/S para Robcmp");
	mvprintw(2, 1, "----------------------------");

	mvprintw(6, 1, "Ultima msg:");

	int currow = 10;
	mvprintw(currow++, 1, "[ Display LCD ]");
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

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

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

void digitalWrite(char port, char value) {
	if (port > ARDUINO_PORTS) {
		attron(COLOR_PAIR(3));
		mvprintw(6, 14, "Erro: porta %d nao existe.",
			port);
		attroff(COLOR_PAIR(3));
	} else {
		arduino_out_ports[port] = value;
	}

	refresh_screen();
}

void delay(int milis) {
	attron(COLOR_PAIR(3));
	mvprintw(6, 14, "Delay %d milis", milis);
	attroff(COLOR_PAIR(3));
	
	refresh_screen();
	usleep(milis*1000);

	mvprintw(6, 14, "                   ");

}

/*int main() {

	int r = 10;
	float d = 100.903;

	print(1, &d);
	print(0, &r);
}
*/
