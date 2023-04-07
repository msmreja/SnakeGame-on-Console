#include <iostream>
#include<conio.h>
#include <windows.h>
using namespace std;

bool gameover;
const int height = 20;
const int width = 50;
int x, y, pointX, pointY, score=0;
enum eDirecction { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecction dir;
int tailX[100], tailY[100];
int TailSize;

void setup() {
  gameover = false;
  dir = STOP;
  x = width / 2;
  y = height / 2;
  pointX = rand() % width;
  pointY = rand() % height;
  score = 0;
}
void draw() {
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout << "_";
    cout << endl;
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "8";
            else if (i == pointY && j == pointX)
                cout << "o";
            else
            {
                bool print = false;
                for (int k = 0; k < TailSize; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "*";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }
 
    for (int i = 0; i < width+2; i++)
        cout << "_";
    cout << endl;
    cout << "Score:" << score << endl;
  
}
void input() {
    if(_kbhit()){
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover=true;
            break;
        }
    }
}
void logic(){
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < TailSize; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    
    if(x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
     else if (y < 0) 
        y = height - 1;
 
    for (int i = 1; i < TailSize; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
 
    if (x == pointX && y == pointY)
    {
        score += 10;
        pointX = rand() % width;
        pointY = rand() % height;
        TailSize++;
    }
}

int main() {
  while (!gameover) {
    draw();
    input();
    logic();
  }
  system("cls");
  cout<<"--------Game Over--------"<<'\n'<<"Your Score is : "<<score<<endl;
  cout<<'\n'<<"Press Enter To Exit..."<<endl;
  cin.get();
}