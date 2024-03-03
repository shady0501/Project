#include <iostream> 
#include <windows.h> 
#include <conio.h> 
using namespace std;


//====��������=========

//------��궨λ-------

void gotoxy(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//------���ع��-------

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


//---------���õ���ɫ-------

#define background_color ' ' 
#define boundary_color '+' //---��ɫ------

#define enemy_color '@' 
#define shooter_color '*' 
#define bullet_color '|' 
//------����λ��------

int  enemy_x, enemy_y;

//------ս��λ��------

int shooter_x, shooter_y;

//------�ӵ�λ��------

int  bullet_x = -1, bullet_y = -1;

//==========����==========

const int canvas_width = 50, canvas_height = 20; //����canvas�ĳ���

char canvas[canvas_height][canvas_width];     //����������һ�����������ַ����ľ��󣨾�������


//---------��ջ���--------

void clear_canvas() {
	for (int y = 0; y < canvas_height; y++)
		for (int x = 0; x < canvas_width; x++)
			canvas[y][x] = background_color;
	int right = canvas_width - 1;
	for (int y = 0; y < canvas_height; y++) {
		canvas[y][0] = boundary_color;
		canvas[y][right] = boundary_color;
	}
	int bottom = canvas_height - 1;
	for (int x = 0; x < canvas_width; x++) {
		canvas[0][x] = boundary_color;
		canvas[bottom][x] = boundary_color;
	}
}



void setup() {
	hideCursor();
	enemy_x = canvas_width / 2;
	enemy_y = 2;

	shooter_x = canvas_width / 2;
	shooter_y = canvas_height - 3;

}

//--------��������--------

void processInput() {
	char key;
	if (_kbhit()) {
		key = _getch();
		if (key == ' ') {
			//�����ӵ���λ��������ս�����Ϸ�

			bullet_x = shooter_x;
			bullet_y = shooter_y - 3;
		}
		else if (key == 'a' || key == 'A') {
			if (shooter_x > 0)  shooter_x--;  //ս������


		}
		else if (key == 'd' || key == 'D') {
			if (shooter_x < canvas_width - 1)      shooter_x++;   //ս������

		}
		else if (key == 'w' || key == 'W') {
			if (shooter_y > 0)            shooter_y--;
		}
		else if (key == 's' || key == 'S') {
			if (shooter_y < canvas_height - 1)	       shooter_y++;
		}
	}

}

//--------��������--------

void update() {
	//�����ӵ�ʱ��ÿ�����»��ƻ���ǰ���ӵ�λ�������ƶ�һ��λ��

	if (bullet_y > 1) bullet_y--;
}

void renderScene() {
	clear_canvas();

	if (enemy_x >= 0 && enemy_x < canvas_width && enemy_y >= 0 && enemy_y < canvas_height)
		canvas[enemy_y][enemy_x] = enemy_color;

	canvas[shooter_y - 1][shooter_x] = shooter_color;
	canvas[shooter_y][shooter_x - 1] = shooter_color;
	canvas[shooter_y][shooter_x] = shooter_color;
	canvas[shooter_y][shooter_x + 1] = shooter_color;
	canvas[shooter_y + 1][shooter_x - 1] = shooter_color;
	canvas[shooter_y + 1][shooter_x + 1] = shooter_color;

	if (bullet_x >= 0 && bullet_x < canvas_width && bullet_y >= 0
		&& bullet_y < canvas_height)
		canvas[bullet_y][bullet_x] = bullet_color;

}


void show() {
	gotoxy(0, 0);
	for (int y = 0; y < canvas_height; y++) {
		for (int x = 0; x < canvas_width; x++)
			std::cout << canvas[y][x];
		std::cout << '\n';
	}
}


int main() {
	setup();

	while (1) {
		processInput();
		update();
		renderScene();
		show();
	}


	return 0;
}