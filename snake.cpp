#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

using namespace std;
CONST int MAP_SIZE = 30;


// Utils
void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void drawCanvas() {
    // TOP
    for (int i = 0; i < MAP_SIZE; i++) {
        cout << "-";
    }

    // BOTTOM
    gotoxy(0, MAP_SIZE);
    for (int i = 0; i < MAP_SIZE; i++) {
        cout << "-";
    }

    // LEFT
    for (int j = 1; j < MAP_SIZE; j++) {
        gotoxy(0, j);
        cout << "|";
    }
    
    // RIGHT
    for (int j = 1; j < MAP_SIZE; j++) {
        gotoxy(MAP_SIZE - 1, j);
        cout << "|";
    }

    // TITLE
    gotoxy(MAP_SIZE + 3, 1);
    cout << "|| SNAKE GAME ||";
}


class Apple {
private:
    int _x;
    int _y;
public:
    Apple() {
        _x = MAP_SIZE / 3;
        _y = MAP_SIZE / 3;
    }

    void spawn() {
        _x = rand() % MAP_SIZE; 
        _y = rand() % MAP_SIZE;
    }
    
    void show_on_xy() {
        gotoxy(_x, _y);
        cout << "*";
    }

    pair<int, int> getAppleCoor() {
        return {_x, _y};
    }
};

class Snake {
private:
    int _x;
    int _y;
    pair<int, int> _dir;

    int _point;
public:
    CONST pair<int, int> UP = {0, -1};
    CONST pair<int, int> DOWN = {0, 1};
    CONST pair<int, int> LEFT = {-1, 0};
    CONST pair<int, int> RIGHT = {1, 0};

    Snake() {
        _x = MAP_SIZE / 2;
        _y = MAP_SIZE / 2;
        _dir = RIGHT;
        _point = 0;
    }

    void show_on_xy() {
        gotoxy(_x, _y);
        cout << "x";      
    }

    void move_dir() {
        _x += _dir.first;
        _y += _dir.second;

        if (_x < 1) _x += MAP_SIZE;
        if (_x > MAP_SIZE - 1) _x = 0;
        if (_y < 1) _y += MAP_SIZE;
        if (_y > MAP_SIZE - 1) _y = 0;
    }

    void set_dir(const pair<int, int>& dir) {
        _dir = dir;
    }

    bool isHitByApple(Apple* apple) {
        pair<int, int> appleCoor = apple->getAppleCoor();
        if (this->_x == appleCoor.first
        &&  this->_y == appleCoor.second) {
            return true;
        }

        return false;
    }

    void increasePoint() {
        _point += 1;
    }

    int getPoint() {
        return _point;
    }
};


void showPoint(Snake* snake) {
    gotoxy(MAP_SIZE + 3, 3);
    cout << "POINT: " << snake->getPoint();
}

int main() {
    srand(time(0));
    Snake* louis = new Snake;
    Apple* apple = new Apple;
    char c;    
    
    int temp = 1000;
    while (temp--) {
        // canvas
        drawCanvas();
        showPoint(louis);

        apple->show_on_xy();
        
        if (louis->isHitByApple(apple)) {
            louis->increasePoint();
            apple->spawn();
        }

        if (kbhit()) {
            c = getch();
        }
        if (toupper(c) == 'W') {
            louis->set_dir(louis->UP);
        }
        if (toupper(c) == 'A') {
            louis->set_dir(louis->LEFT);
        }
        if (toupper(c) == 'S') {
            louis->set_dir(louis->DOWN);
        }
        if (toupper(c) == 'D') {
            louis->set_dir(louis->RIGHT);
        }

        louis->move_dir();
        louis->show_on_xy();
        // apple->spawn();

        // refresh screen
        Sleep(50);
        system("cls");
    }


    // while (true) {
    //     if (_kbhit) {
    //         cout << _getch() << endl;
    //     }
    // }
    return 0;
}