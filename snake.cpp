#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <vector>

using namespace std;
CONST int MAP_SIZE = 30;
CONST int GAME_TICK = 30;

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

struct Coordinate {
    int _x;
    int _y;

    bool operator==(const Coordinate& coor)  {
        return (_x == coor._x && _y == coor._y);
    }
};

class Apple {
private:
    Coordinate pos;
public:
    Apple() {
        pos._x = MAP_SIZE / 3;
        pos._y = MAP_SIZE / 3;
    }

    void spawn() {
        pos._x = rand() % MAP_SIZE; 
        pos._y = rand() % MAP_SIZE;
    }
    
    void show_on_xy() {
        gotoxy(pos._x, pos._y);
        cout << "*";
    }

    Coordinate getAppleCoor() {
        return pos; 
    }
};

class Snake {
private:
    // head coor should be put on last element of pos
    // for easy to push back
    // rather than shift entine the array
    vector<Coordinate> pos;
    pair<int, int> _dir;

    int _point;
public:
    CONST pair<int, int> UP = {0, -1};
    CONST pair<int, int> DOWN = {0, 1};
    CONST pair<int, int> LEFT = {-1, 0};
    CONST pair<int, int> RIGHT = {1, 0};

    Snake() {
        pos.clear();
        pos.push_back({MAP_SIZE / 2, MAP_SIZE / 2});
        _dir = RIGHT;
        _point = 0;
    }

    void show_on_xy() {
        for (auto p : pos) {
            gotoxy(p._x, p._y);
            cout << "x";      
        }
    }

    void move_dir() {
        int posSize = pos.size();

        // only run this if snake's length > 1
        if (posSize > 1) {
            // shift coordinate arrays
            for (int i = 0; i < posSize - 1; i++) {
                pos[i] = pos[i + 1];
            }
        }

        // calc new head
        pos[posSize - 1]._x += _dir.first;
        pos[posSize - 1]._y += _dir.second;
        
        // out of bound cases
        // LEFT
        if (pos[posSize - 1]._x < 1) pos[posSize - 1]._x += MAP_SIZE;
        // RIGHT
        if (pos[posSize - 1]._x > MAP_SIZE - 1) pos[posSize - 1]._x = 0;
        // UP
        if (pos[posSize - 1]._y < 1) pos[posSize - 1]._y += MAP_SIZE;
        // DOWN
        if (pos[posSize - 1]._y > MAP_SIZE - 1) pos[posSize - 1]._y = 0;
    }

    void set_dir(const pair<int, int>& dir) {
        _dir = dir;
    }

    pair<int, int> get_dir() {
        return _dir;
    }

    bool isHitByApple(Apple* apple) {
        Coordinate appleCoor = apple->getAppleCoor();
        if (this->pos[pos.size() - 1]._x + _dir.first == appleCoor._x
        &&  this->pos[pos.size() - 1]._y + _dir.second == appleCoor._y) {
            return true;
        }

        return false;
    }

    void HitByApple(Apple* apple) {
        _point += 1;

        // push new head to snake
        // from apple position
        auto applePos = apple->getAppleCoor();
        pos.push_back({applePos._x, applePos._y});
    }

    bool isHitItsSelf() {
        Coordinate head = pos[pos.size() - 1];
        for (int i = 0; i < pos.size() - 1; i++) {
            if (head == pos[i]) {
                return true;
            }
        }

        return false;
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
    
    // int temp = 1000;
    while (true) {
        // canvas
        drawCanvas();
        showPoint(louis);

        if (louis->isHitItsSelf()) {
            break;
        }

        if (louis->isHitByApple(apple)) {
            louis->HitByApple(apple);
            apple->spawn();
        }

        if (kbhit()) {
            c = getch();
        }
        if (toupper(c) == 'W') {
            if (louis->get_dir() != louis->DOWN) {
                louis->set_dir(louis->UP);
            }
        }
        if (toupper(c) == 'A') {
            if (louis->get_dir() != louis->RIGHT) {
                louis->set_dir(louis->LEFT);
            }
        }
        if (toupper(c) == 'S') {
            if (louis->get_dir() != louis->UP) {
                louis->set_dir(louis->DOWN);
            }
        }
        if (toupper(c) == 'D') {
            if (louis->get_dir() != louis->LEFT) {
                louis->set_dir(louis->RIGHT);
            }
        }

        apple->show_on_xy();
        louis->move_dir();
        louis->show_on_xy();
        // apple->spawn();

        // refresh screen
        Sleep(1000 / GAME_TICK);
        system("cls");
    }

    return 0;
}