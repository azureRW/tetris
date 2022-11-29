#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void background_output(int, int);
void matrix_output(int);
void matrix_output(int matrix[12][22][2]);
void set_background(int matrix[12][22][2]);
void set_testblock(int matrix[12][22][2]);
void moving_down_test(int matrix[12][22][2]);
void moving_right_test(int matrix[12][22][2]);
void moving_left_test(int matrix[12][22][2]);
void getkeyboard_n_output(int matrix[12][22][2]);
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

    set_background(matrix); // the instruction makes the main matrix print the frame of game
    //* matrix_output(matrix); //the instruction print matrix on cmd
    // the form of the input matrix is a [12][22][2] matrix [12] for x [22] for y [2] will be the characteristics of the blocks
    set_testblock(matrix);
    matrix_output(matrix);
    
    //getkeyboard_n_output(matrix);
    

    
    
    

    

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
    int k = 0;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {

            if (matrix[j][i][0] > 0)
            {
                k = 1;
            }
            else
            {
                k = 0;
            }

            switch (k)
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
void set_testblock(int matrix[12][22][2])
{
    matrix[5][1][0] = 2;
    matrix[5][1][1] = 2;
}
void moving_down_test(int matrix[12][22][2])
{
    int k = 1;
    int l = 0;
    int x = 0;
    int y = 0;
    int z1 = 0;
    int z2 = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][1] > 1)
            {
                k = 0;
                l = matrix[j][i][1];
                x = j;
                y = i;
                z1 = matrix[j][i][0];
                z2 = matrix[j][i][1];
                goto here;
            }
        }
    }
here:
    matrix[x][y][0] = 0;
    matrix[x][y][1] = 0;
    matrix[x][y + 1][0] = z1;
    matrix[x][y + 1][1] = z2;
}
void moving_right_test(int matrix[12][22][2])
{
    int k = 1;
    int l = 0;
    int x = 0;
    int y = 0;
    int z1 = 0;
    int z2 = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][1] > 1)
            {
                k = 0;
                l = matrix[j][i][1];
                x = j;
                y = i;
                z1 = matrix[j][i][0];
                z2 = matrix[j][i][1];
                goto here;
            }
        }
    }
here:
    matrix[x][y][0] = 0;
    matrix[x][y][1] = 0;
    matrix[x + 1][y][0] = z1;
    matrix[x + 1][y][1] = z2;
}
void moving_left_test(int matrix[12][22][2])
{
    int k = 1;
    int l = 0;
    int x = 0;
    int y = 0;
    int z1 = 0;
    int z2 = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][1] > 1)
            {
                k = 0;
                l = matrix[j][i][1];
                x = j;
                y = i;
                z1 = matrix[j][i][0];
                z2 = matrix[j][i][1];
                goto here;
            }
        }
    }
here:
    matrix[x][y][0] = 0;
    matrix[x][y][1] = 0;
    matrix[x - 1][y][0] = z1;
    matrix[x - 1][y][1] = z2;
}
void getkeyboard_n_output(int matrix[12][22][2])
{
    
    int c2;
    c2 = getch();
   
    if (c2==224){
        c2=getch();
        }
    system("cls");
    
    switch (c2)
    {

    case 80: // down
        moving_down_test(matrix);
        break;
    case 75: // left
        moving_left_test(matrix);
        break;
    case 77: // right
        moving_right_test(matrix);
        break;
    default:
        break;
    }
    matrix_output(matrix);
}
