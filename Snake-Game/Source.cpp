#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h> 
using namespace std;

void printMap();
void initMap();
void clearScreen();
void generateFood();

char getMapValue(int value);

const int mapwidth = 20;
const int mapheight = 20;
int map[mapwidth * mapheight];
int headxpos;
int headypos;
int direction;

bool running;

int main()
{
    run();
    return 0;
}

void clearScreen() {
    system("cls");
}

void run()
{

}

void initMap() // Khởi tạo vị trí và hướng ban đầu của con rắn
{
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    direction = 1; // Hướng ban đầu sang phải

    // Khởi tạo rắn dài 4 ô
    for (int i = 0; i < snakeLength; ++i) {
        map[(headxpos - i) + headypos * mapwidth] = snakeLength - i;
    }

    // Tạo tường xung quanh bản đồ
    for (int x = 0; x < mapwidth; ++x) {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }
    for (int y = 0; y < mapheight; y++) {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }
    generateFood(); // Sinh thức ăn đầu tiên
}

void printMap() // In bản đồ ra màn hình
{
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            cout << getMapValue(map[x + y * mapwidth]);
        }
        cout << endl;
    }
}

// Hàm trả về ký tự tương ứng với giá trị trên bản đồ 
char getMapValue(int value)
{
    if (value > 0) return 'o';
    switch (value) {// Thân rắn
    case -1: return 'X';// Tường
    case -2: return 'O';// Thức ăn
    }
    return ' ';// Ô trống
}