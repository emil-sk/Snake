#include <iostream>
#include <conio.h>
#include <chrono>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 22;
const int height = 22;
int xSnake, ySnake, xFruit, yFruit, score;

enum eDirection {stop = 0, Left, Right, Up, Down };
eDirection dir;

int xSnakePositions[200];
int ySnakePositions[200];
int tailLength;

void Draw() 
{
    system("cls");
    for (int i = 0; i < width; i++)
    {
        cout << '#';
        cout << " ";
    }
    cout << endl;

    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 2)
            {
                cout << '#';
                cout << " ";
            }
            if (i == ySnake && j == xSnake) 
            {
                cout << "O";
                cout << " ";
            }
            else if (i == yFruit && j == xFruit) 
            {
                cout << "F";
                cout << " ";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < tailLength; k++)
                {
                    if (xSnakePositions[k] == j && ySnakePositions[k] == i)
                    {
                        cout << "o";
                        cout << " ";
                        print = true;
                    }

                }
                    if (!print)
                    {
                        cout << "  ";
                    }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
    {
        cout << '#';
        cout << " ";
    }
    cout << endl;
    cout << "Score: " << score << "\n";
    cout << "Controls: WASD";
}

void Input() 
{
    int prevX = xSnakePositions[0];
    int prevY = ySnakePositions[0];
    xSnakePositions[0] = xSnake;
    ySnakePositions[0] = ySnake;
    for (int i = 1; i < tailLength; i++)
    {
        int prev2x = xSnakePositions[i];
        int prev2y = ySnakePositions[i];
        xSnakePositions[i] = prevX;
        ySnakePositions[i] = prevY;
        prevX = prev2x;
        prevY = prev2y;
    }
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = Up;
            break;
        case 's':
            dir = Down;
            break;
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        default:
            break;
        }
    }
}

void Movement() 
{
        switch (dir)
        {
        case Up:
            ySnake--;
            break;
        case Down:
            ySnake++;
            break;
        case Left:
            xSnake--;
            break;
        case Right:
            xSnake++;
            break;
        }

    if (xSnake < 0 || xSnake >= width - 2 || ySnake < 0 || ySnake >= height) 
    {
        gameOver = true;
    }

    if (xSnake == xFruit && ySnake == yFruit) 
    {
        score++;
        tailLength++;
        xFruit = rand() % (width-2);
        yFruit = rand() % (height-2);
    }

    for (int i = 0; i < tailLength; i++) 
    {
        if (xSnake == xSnakePositions[i] && ySnake == ySnakePositions[i]) 
        {
            gameOver = true;
        }
    }
}

int main()
{
    srand(time(0));
    int xPos = width - 2;
    int yPos = height - 2;
    gameOver = false;
    xSnake = width / 2;
    ySnake = height / 2;
    xFruit = rand() % (xPos);
    yFruit = rand() % (yPos);
    score = 0;

    while (!gameOver)
    {
        Draw();
        Input();
        Movement();
        Sleep(100);
    }
    return 0;
}