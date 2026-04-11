#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y; // g³owa wê¿a
int foodX, foodY;
int score;
int tailX[100], tailY[100];
int nTail;

void Setup() {
    gameOver = false;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
    nTail = 0;
    dir = STOP;
}

void Draw() {
    cout << "\x1B[2J\x1B[H"; // czyœci ekran

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O"; // g³owa
            else if (i == foodY && j == foodX)
                cout << "F"; // jedzenie
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
            if (!print)
                cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': if (dir != RIGHT) dir = LEFT; break;
        case 'd': if (dir != LEFT) dir = RIGHT; break;
        case 'w': if (dir != DOWN) dir = UP; break;
        case 's': if (dir != UP) dir = DOWN; break;
        case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = x;
    int prevY = y;

    // ruch g³owy
    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    default: break;
    }
    // ogon
    int prev2X, prev2Y;
    for (int i = 0; i < nTail; i++) {
        if (i == 0) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
        } else {
            int tempX = tailX[i];
            int tempY = tailY[i];
            tailX[i] = prev2X;
            tailY[i] = prev2Y;
            prev2X = tempX;
            prev2Y = tempY;
        }
    }
    // kolizje ze sciana
    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    // kolizje z ogonem
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // jedzenie
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(200);
    }

    cout << "Game Over!" << endl;
    return 0;
}
