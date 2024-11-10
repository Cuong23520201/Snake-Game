#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h> 
using namespace std;

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();

char getMapValue(int value);

const int mapwidth = 20;
const int mapheight = 20;
int snakeLength = 4;
int map[mapwidth * mapheight];
int headxpos;
int headypos;
int direction;
int food = 0;
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
    initMap();
    running = true;
    while (running) {
        if (_kbhit()) {
            changeDirection(_getch());
        }
        update();
        clearScreen();
        printMap();
        Sleep(400);
    }

    cout << "\t\tGame Over!" << endl << "\t\tYour score is: " << food;
    cin.ignore();
}

void changeDirection(char key) {
    switch (key) {
    case 72: // Mũi tên lên
        if (direction != 2) direction = 0;
        break;
    case 77: // Mũi tên phải
        if (direction != 3) direction = 1;
        break;
    case 80: // Mũi tên xuống
        if (direction != 0) direction = 2;
        break;
    case 75: // Mũi tên trái
        if (direction != 1) direction = 3;
        break;
    }
}


// Di chuyển con rắn và xử lý logic khi gặp thức ăn
void move(int dx, int dy) {
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Kiểm tra nếu con rắn gặp thức ăn
    if (map[newx + newy * mapwidth] == -2) {
        food++;           // Tăng điểm
        snakeLength++;    // Tăng chiều dài con rắn
        generateFood();   // Sinh thức ăn mới
    }
    else if (map[newx + newy * mapwidth] != 0) { // Nếu gặp tường hoặc chính nó thì kết thúc trò chơi
        running = false;
    }
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = snakeLength;
}

// Sinh ngẫu nhiên thức ăn trên bản đồ
void generateFood() {
    int x = 0;
    int y = 0;
    do {
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;
    } while (map[x + y * mapwidth] != 0); // Đảm bảo thức ăn không sinh đè lên con rắn
    map[x + y * mapwidth] = -2;
}

void update() { // Cập nhật hướng di chuyển của rắn
    switch (direction) {
    case 0: move(-1, 0); // Di chuyển lên
        break;
    case 1: move(0, 1); // Di chuyển phải
        break;
    case 2: move(1, 0); // Di chuyển xuống
        break;
    case 3: move(0, -1); //Di chuyển trái
        break;
    }
    // Giảm giá trị của mỗi phần tử trên bản đồ để cập nhật vị trí của các đoạn thân rắn
    for (int i = 0; i < mapwidth * mapheight; i++) {
        if (map[i] > 0) map[i]--;
    }
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