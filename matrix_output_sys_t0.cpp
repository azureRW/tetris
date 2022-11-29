#include <iostream>
#include <windows.h>
using namespace std;

void background_output(int, int);
void matrix_output(int);
void matrix_output(int matrix[12][22][2]);
void set_background(int matrix[12][22][2]);

void SetColor(int f = 7, int b = 0) // a fumction in windows.h can change font color
{
    unsigned short ForeColor = f + 16 * b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, ForeColor);
}

int main()
{
    int matrix[12][22][2] = {0};

    system("chcp 65001");
    system("cls");

    set_background(matrix);
    matrix_output(matrix);
    cout << "\n";

    // background_output(0,0);
    SetColor();
    system("pause");
    return 0;
}



void background_output(int shiftx = 0, int shifty = 0)

{
    for (int i = 0; i < shifty; i++)
    {
        cout << "\n";
    }
    for (int i = 0; i < shiftx; i++)
    {
        cout << "  ";
    }
    for (int i = 0; i < 12; i++)
    {
        cout << "██";
    }
    cout << "\n";
    for (int i = 0; i < 20; i++)
    {
        for (int i = 0; i < shiftx; i++)
        {
            cout << "  ";
        }
        cout << "██                    ██"
             << "\n";
    }
    for (int i = 0; i < shiftx; i++)
    {
        cout << "  ";
    }
    for (int i = 0; i < 12; i++)
    {
        cout << "██";
    }
}

void matrix_output(int matrix[12][22][2])
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            switch (matrix[j][i][0])
            {
            case 1:
                SetColor(matrix[j][i][1], 0);
                cout << "██";
                break;
            case 0:
                cout << "  ";
                break;
            }
        }
        cout << "\n";
    }
}
void set_background(int matrix[12][22][2])
{
    for (int i = 0; i < 12; i++)
    {
        matrix[i][0][0] = 1;
        matrix[i][0][1] = 7;
        matrix[i][21][0] = 1;
        matrix[i][21][1] = 7;
    }
    for (int i = 0; i < 22; i++)
    {
        matrix[0][i][0] = 1;
        matrix[0][i][1] = 7;
        matrix[11][i][0] = 1;
        matrix[11][i][1] = 7;
    }
}