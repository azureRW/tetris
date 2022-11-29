#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void background_output(int, int);
void matrix_output(int);
void matrix_output(int matrix[12][22][4]);
void set_background(int matrix[12][22][4]);
int moving_down_test(int matrix[12][22][4]);
int moving_right_test(int matrix[12][22][4]);
int moving_left_test(int matrix[12][22][4]);
int getkeyboard(void); // originally, this instruction included output and blockmoving, but I separated it.
void blolckmoving(int matrix[12][22][4], int i);
void SetColor(int f = 7, int b = 0) // a fumction in windows.h can change font color
{
    unsigned short ForeColor = f + 16 * b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, ForeColor);
}
int set7blocks(int matrix[12][22][4], int i); // re0-4:circle; re1-3:long; re2-14:凸;
                                              // re3-5:znti Z; re4-6:Z; re5-2:L; re6-1:anti L;
void blocks_collision_test(int matrix[12][22][4], int matrix_t[12][22][4], int checking_instruction);
int recode4block(int matrix[12][22][4], int recodedblock_1[4][6]);
int recode5block(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2]);
void matrixequa(int matrix[12][22][4], int matrix_t[12][22][4]); // let latter matrix equal to former
int newspace_check(int matrix[12][22][4], int recodedblock_1[4][6]);
void unmovable(int matrix[12][22][4], int recodedblock_1[4][6]);
int movingblockerasing(int matrix[12][22][4]);
void putback(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2]);
void matrix_contemt_opt(int matrix[12][22][4], int k);
int block_rotation(int matrix[12][22][4], int matrix_t[12][22][4], int mode, int blocktype); // mode: 72 for clockwise , 120 for counterclockwise
int search_r(int matrix[12][22][4], int coordinate[2]);
int search_I(int matrix[12][22][4], int coordinate[4]);
int I_rotation(int matrix[12][22][4], int matrix_t[12][22][4], int mode);
int inputselection(int key);
int movingcase80(int matrix[12][22][4], int matrix_t[12][22][4]);
int movingcase77(int matrix[12][22][4], int matrix_t[12][22][4]);
int movingcase75(int matrix[12][22][4], int matrix_t[12][22][4]);
int main()
{
    int matrix[12][22][4] = {0};
    int matrix_t[12][22][4] = {0};
    int recodedblock_1[4][6] = {0}; // {block x axis,block y axis,z1,z2,z3}
    int recodedblock_3[4][6] = {0};
    int kernel2[2] = {0};
    int shapeofyou;
    system("chcp 65001");
    system("cls");

    set_background(matrix_t);
    set_background(matrix); // the instruction makes the main matrix print the frame of game
    //*matrix_output(matrix); //the instruction print matrix on cmd
    // the form of the input matrix is a [12][22][2] matrix [12] for x [22] for y [2] will be the characteristics of the blocks
    //*set7blocks(matrix, 1);

    shapeofyou = set7blocks(matrix, 1);
    matrixequa(matrix, matrix_t);
    matrix_output(matrix);

    for (int j = 0;; j++)
    {
        int key = 0;
        int sl = 0;
        key = getkeyboard();
        sl = inputselection(key);
        switch (sl)
        {
        case 0:
            break;

        case 1:
            blocks_collision_test(matrix, matrix_t, key);
            matrix_output(matrix);
            cout<<"\n";
            matrix_contemt_opt(matrix,3);
            

            break;
        case 2:
            block_rotation(matrix, matrix_t, key, shapeofyou);
            matrix_output(matrix);
            

            break;
        }

        if (recode5block(matrix, recodedblock_3, kernel2) == 0)
        {

            shapeofyou = set7blocks(matrix, 5);
            matrixequa(matrix, matrix_t);
            matrix_output(matrix);
        }
    }

    // background_output(0,0);

    system("pause");
    SetColor();
    return 0;
}
void matrixequa(int matrix[12][22][4], int matrix_t[12][22][4])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            matrix_t[i][j][0] = matrix[i][j][0];
            matrix_t[i][j][1] = matrix[i][j][1];
            matrix_t[i][j][2] = matrix[i][j][2];
            matrix_t[i][j][3] = matrix[i][j][3];
        }
    }
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
void matrix_output(int matrix[12][22][4])
{
    system("cls");
    int k = 0;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {

            switch (matrix[j][i][1])
            {
            case 1:
                SetColor(matrix[j][i][0], 0);
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
void set_background(int matrix[12][22][4])
{
    for (int i = 0; i < 12; i++)
    {
        matrix[i][0][0] = 7;
        matrix[i][21][0] = 7;
        matrix[i][0][1] = 1;
        matrix[i][21][1] = 1;
    }
    for (int i = 0; i < 22; i++)
    {
        matrix[0][i][0] = 7;
        matrix[11][i][0] = 7;
        matrix[0][i][1] = 1;
        matrix[11][i][1] = 1;
    }
}
int moving_down_test(int matrix[12][22][4])
{
    int a[2] = {0};
    int b[4] = {0};
    int block_num = 0;
    int x[4] = {0};
    int y[4] = {0};
    int z[4] = {0};
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][2] == 1)
            {
                x[block_num] = j;
                y[block_num] = i;
                z[0] = matrix[j][i][0];
                z[1] = matrix[j][i][1];
                z[2] = matrix[j][i][2];

                matrix[j][i][0] = 0;
                matrix[j][i][1] = 0;
                matrix[j][i][2] = 0;

                block_num++;
                if (block_num == 4)
                {
                    goto here;
                }
            }
        }
    }
    goto there;
here:
    for (int i = 0; i < 4; i++)
    {

        matrix[x[i]][y[i] + 1][0] = z[0];
        matrix[x[i]][y[i] + 1][1] = z[1];
        matrix[x[i]][y[i] + 1][2] = z[2];
    }
    if (matrix[x[0]][y[0]][0] != 3 && matrix[x[0]][y[0]][0] != 4)
    {
        search_r(matrix, a);
        matrix[a[0]][a[1]][3] = 0;
        matrix[a[0]][a[1] + 1][3] = 1;
    }
    else if (matrix[x[0]][y[0]][0] == 3)
    {
        search_I(matrix, b);
        matrix[b[0]][b[1]][3] = 0;
        matrix[b[0]][b[1] + 1][3] = 1;
        matrix[b[2]][b[3]][3] = 0;
        matrix[b[2]][b[3] + 1][3] = 1;
    }
    else
    {
        goto there;
    }

there:
    return 0;
}
int moving_right_test(int matrix[12][22][4])
{
    int a[2] = {0};
    int b[4] = {0};
    int block_num = 0;
    int x[4] = {0};
    int y[4] = {0};
    int z[4] = {0};
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][2] == 1)
            {
                x[block_num] = j;
                y[block_num] = i;
                z[0] = matrix[j][i][0];
                z[1] = matrix[j][i][1];
                z[2] = matrix[j][i][2];

                matrix[j][i][0] = 0;
                matrix[j][i][1] = 0;
                matrix[j][i][2] = 0;

                block_num++;
                if (block_num == 4)
                {
                    goto here;
                }
            }
        }
    }
    goto there;
here:
    for (int i = 0; i < 4; i++)
    {

        matrix[x[i] + 1][y[i]][0] = z[0];
        matrix[x[i] + 1][y[i]][1] = z[1];
        matrix[x[i] + 1][y[i]][2] = z[2];
    }
    if (matrix[x[0]][y[0]][0] != 3 && matrix[x[0]][y[0]][0] != 4)
    {
        search_r(matrix, a);
        matrix[a[0]][a[1]][3] = 0;
        matrix[a[0] + 1][a[1]][3] = 1;
    }
    else if (matrix[x[0]][y[0]][0] == 3)
    {
        search_I(matrix, b);
        matrix[b[0]][b[1]][3] = 0;
        matrix[b[0] + 1][b[1]][3] = 1;
        matrix[b[2]][b[3]][3] = 0;
        matrix[b[2] + 1][b[3]][3] = 1;
    }
    else
    {
        goto there;
    }
there:
    return 0;
}
int moving_left_test(int matrix[12][22][4])
{
    int a[2] = {0};
    int b[4] = {0};
    int block_num = 0;
    int x[4] = {0};
    int y[4] = {0};
    int z[4] = {0};
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][2] == 1)
            {
                x[block_num] = j;
                y[block_num] = i;
                z[0] = matrix[j][i][0];
                z[1] = matrix[j][i][1];
                z[2] = matrix[j][i][2];

                matrix[j][i][0] = 0;
                matrix[j][i][1] = 0;
                matrix[j][i][2] = 0;

                block_num++;
                if (block_num == 4)
                {
                    goto here;
                }
            }
        }
    }
    goto there;
here:
    for (int i = 0; i < 4; i++)
    {

        matrix[x[i] - 1][y[i]][0] = z[0];
        matrix[x[i] - 1][y[i]][1] = z[1];
        matrix[x[i] - 1][y[i]][2] = z[2];
    }
    if (matrix[x[0]][y[0]][0] != 3 && matrix[x[0]][y[0]][0] != 4)
    {
        search_r(matrix, a);
        matrix[a[0]][a[1]][3] = 0;
        matrix[a[0] - 1][a[1]][3] = 1;
    }
    else if (matrix[x[0]][y[0]][0] == 3)
    {
        search_I(matrix, a);
        matrix[b[0]][b[1]][3] = 0;
        matrix[b[0] - 1][b[1]][3] = 1;
        matrix[b[2]][b[3]][3] = 0;
        matrix[b[2] - 1][b[3]][3] = 1;
    }
    else
    {
        goto there;
    }
there:
    return 0;
}
int getkeyboard(void)
{

    int c2;
    c2 = getch();

    if (c2 == 224)
    {
        c2 = getch();
    }
    system("cls");

    return c2;
}
void blolckmoving(int matrix[12][22][4], int i)
{
    switch (i)
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
}
int set7blocks(int matrix[12][22][4], int i)
{
    int re;
    switch (i)
    {
    case 0: // red circle
        matrix[5][1][0] = 4;
        matrix[6][1][0] = 4;
        matrix[5][2][0] = 4;
        matrix[6][2][0] = 4;
        matrix[5][1][1] = 1;
        matrix[6][1][1] = 1;
        matrix[5][2][1] = 1;
        matrix[6][2][1] = 1;
        matrix[5][1][2] = 1;
        matrix[6][1][2] = 1;
        matrix[5][2][2] = 1;
        matrix[6][2][2] = 1;
        re = 0;
        break;
    case 1: // blue long
        matrix[4][1][0] = 3;
        matrix[5][1][0] = 3;
        matrix[6][1][0] = 3;
        matrix[7][1][0] = 3;
        matrix[4][1][1] = 1;
        matrix[5][1][1] = 1;
        matrix[6][1][1] = 1;
        matrix[7][1][1] = 1;
        matrix[4][1][2] = 1;
        matrix[5][1][2] = 1;
        matrix[6][1][2] = 1;
        matrix[7][1][2] = 1;

        matrix[4][1][3] = 1;
        matrix[7][1][3] = 1;
        re = 1;
        break;
    case 2: // yellow(凸)
        matrix[5][2][0] = 14;
        matrix[5][1][0] = 14;
        matrix[4][2][0] = 14;
        matrix[6][2][0] = 14;
        matrix[5][2][1] = 1;
        matrix[5][1][1] = 1;
        matrix[4][2][1] = 1;
        matrix[6][2][1] = 1;
        matrix[5][2][2] = 1;
        matrix[5][1][2] = 1;
        matrix[4][2][2] = 1;
        matrix[6][2][2] = 1;

        matrix[5][1][3] = 1;
        re = 2;
        break;
    case 3: // purple anti Z
        matrix[4][1][0] = 5;
        matrix[5][1][0] = 5;
        matrix[5][2][0] = 5;
        matrix[6][2][0] = 5;
        matrix[4][1][1] = 1;
        matrix[5][1][1] = 1;
        matrix[5][2][1] = 1;
        matrix[6][2][1] = 1;
        matrix[4][1][2] = 1;
        matrix[5][1][2] = 1;
        matrix[5][2][2] = 1;
        matrix[6][2][2] = 1;

        matrix[5][1][3] = 1;
        re = 3;
        break;
    case 4: // shit Z
        matrix[4][2][0] = 6;
        matrix[5][2][0] = 6;
        matrix[5][1][0] = 6;
        matrix[6][1][0] = 6;
        matrix[4][2][1] = 1;
        matrix[5][2][1] = 1;
        matrix[5][1][1] = 1;
        matrix[6][1][1] = 1;
        matrix[4][2][2] = 1;
        matrix[5][2][2] = 1;
        matrix[5][1][2] = 1;
        matrix[6][1][2] = 1;

        matrix[5][1][3] = 1;
        re = 4;
        break;
    case 5: // green L
        matrix[4][2][0] = 2;
        matrix[5][2][0] = 2;
        matrix[6][2][0] = 2;
        matrix[6][1][0] = 2;
        matrix[4][2][1] = 1;
        matrix[5][2][1] = 1;
        matrix[6][2][1] = 1;
        matrix[6][1][1] = 1;
        matrix[4][2][2] = 1;
        matrix[5][2][2] = 1;
        matrix[6][2][2] = 1;
        matrix[6][1][2] = 1;

        matrix[5][1][3] = 1;
        re = 4;
        break;
    case 6: // darkblue anti L
        matrix[4][2][0] = 1;
        matrix[5][2][0] = 1;
        matrix[6][2][0] = 1;
        matrix[4][1][0] = 1;
        matrix[4][2][1] = 1;
        matrix[5][2][1] = 1;
        matrix[6][2][1] = 1;
        matrix[4][1][1] = 1;
        matrix[4][2][2] = 1;
        matrix[5][2][2] = 1;
        matrix[6][2][2] = 1;
        matrix[4][1][2] = 1;

        matrix[5][1][3] = 1;
        re = 6;
        break;
    }
    return re;
}
void blocks_collision_test(int matrix[12][22][4], int matrix_t[12][22][4], int checking_instruction)
{

    switch (checking_instruction) // instruction=key_name
    {

    case 80:
        movingcase80(matrix, matrix_t);
        break;

    case 122:
        for (int i = 0; i < 21; i++)
        {
            movingcase80(matrix, matrix_t);
        }

        break;
    case 75:

        movingcase75(matrix, matrix_t);
        break;
    case 77:

        movingcase77(matrix, matrix_t);
        break;
    }
}
int recode4block(int matrix[12][22][4], int recodedblock_1[4][6])
{
    int block_num = 0;
    int x[4] = {0};
    int y[4] = {0};
    int z[4] = {0};
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][2] == 1)
            {
                x[block_num] = j;
                y[block_num] = i;
                z[0] = matrix[j][i][0];
                z[1] = matrix[j][i][1];
                z[2] = matrix[j][i][2];

                block_num++;
                if (block_num == 4)
                {
                    goto here;
                }
            }
        }
    }
    goto there;
here:
    for (int i = 0; i < 4; i++)
    {
        recodedblock_1[i][0] = x[i];
        recodedblock_1[i][1] = y[i];
        recodedblock_1[i][2] = z[0];
        recodedblock_1[i][3] = z[1];
    }
there:
    return block_num;
}
int newspace_check(int matrix[12][22][4], int recodedblock_2[4][6])
{
    int block_warmming = 0;
    for (int i = 0; i < 4; i++)
    {
        if (matrix[recodedblock_2[i][0]][recodedblock_2[i][1]][1] == 1)
        {
            block_warmming = 1;
            goto here;
        }
    }
here:
    return block_warmming;
}
void unmovable(int matrix[12][22][4], int recodedblock_1[4][6])
{
    int a[2] = {0};
    for (int i = 0; i < 4; i++)
    {
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][2] = 0;
    }
    if (matrix[recodedblock_1[0][0]][recodedblock_1[0][1]][0] != 4)
    {
        search_r(matrix, a);
        matrix[a[0]][a[1]][3] = 0;
        if (matrix[recodedblock_1[0][0]][recodedblock_1[0][1]][0] == 3)
        {
            search_r(matrix, a);
            matrix[a[0]][a[1]][3] = 0;
        }
    }
}
int movingblockerasing(int matrix[12][22][4])
{
    int block_num = 0;
    int x[4] = {0};
    int y[4] = {0};
    int z[4] = {0};
    int a[2] = {0};
    int flag = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][2] == 1)
            {

                matrix[j][i][0] = 0;
                matrix[j][i][1] = 0;
                matrix[j][i][2] = 0;
                if (matrix[j][i][0] == 3)
                {
                    flag++;
                }

                block_num++;
                if (block_num == 4)
                {
                    goto here;
                }
            }
        }
    }

here:
    search_r(matrix, a);
    matrix[a[0]][a[1]][3] = 0;
    if (flag > 0)
    {
        search_r(matrix, a);
        matrix[a[0]][a[1]][3] = 0;
    }
    return 0;
}
void putback(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2])
{
    int a[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][0] = recodedblock_1[i][2];
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][1] = recodedblock_1[i][3];
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][2] = recodedblock_1[i][4];
    }
    if (recodedblock_1[0][5] != 3 && recodedblock_1[0][5] != 4)
    {
        matrix[kernel[0]][kernel[1]][3] = 1;
    }
    else
    {
    }
}
void matrix_contemt_opt(int matrix[12][22][4], int k)
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            cout << matrix[j][i][k] << " , ";
        }
        cout << "\n";
    }
}
int block_rotation(int matrix[12][22][4], int matrix_t[12][22][4], int mode, int blocktype)
{
    int c = 0;
    int a[2] = {0};
    int a2[2] = {0}; // in this function kernel is a
    int nine_1[9][4] = {0};
    int rot = 0;
    int kernel[2] = {0};
    int b[4][6]; // recodedblock

    ///// //the part used to check that kernel is not stick on the wall
    search_r(matrix, a);
    if (blocktype != 0 && blocktype != 1)
    {

        if (a[1] == 1)
        {
            c = movingcase80(matrix, matrix_t);
            search_r(matrix, a);
            if (c == 0) // if block had been moved, this tern would be 1
                goto here;
        }
        if (a[0] == 1)
        {
            c = movingcase77(matrix, matrix_t);
            search_r(matrix, a);
            if (c == 0)
                goto here;
        }

        if (a[0] == 10)
        {
            c = movingcase75(matrix, matrix_t);
            search_r(matrix, a);
            if (c == 0)
                goto here;
        }
        if (a[1] == 20)
        {
            goto here;
        }
    }
    ////////////////////////////////////////recode the 8 blocks around the kernel
    for (int i = 0; i < 4; i++)
    {
        nine_1[0][i] = matrix[a[0] - 1][a[1] - 1][i];
        nine_1[1][i] = matrix[a[0]][a[1] - 1][i];
        nine_1[2][i] = matrix[a[0] + 1][a[1] - 1][i];
        nine_1[3][i] = matrix[a[0] - 1][a[1]][i];
        nine_1[4][i] = matrix[a[0]][a[1]][i];
        nine_1[5][i] = matrix[a[0] + 1][a[1]][i];
        nine_1[6][i] = matrix[a[0] - 1][a[1] + 1][i];
        nine_1[7][i] = matrix[a[0]][a[1] + 1][i];
        nine_1[8][i] = matrix[a[0] + 1][a[1] + 1][i];
    }

    movingblockerasing(matrix);
    switch (mode)
    {
    case 72:
        if (nine_1[6][2] == 1 && matrix[a[0] - 1][a[1] - 1][1] == 0)
            rot++;
        if (nine_1[3][2] == 1 && matrix[a[0]][a[1] - 1][1] == 0)
            rot++;
        if (nine_1[0][2] == 1 && matrix[a[0] + 1][a[1] - 1][1] == 0)
            rot++;
        if (nine_1[7][2] == 1 && matrix[a[0] - 1][a[1]][1] == 0)
            rot++;
        if (nine_1[1][2] == 1 && matrix[a[0] + 1][a[1]][1] == 0)
            rot++;
        if (nine_1[8][2] == 1 && matrix[a[0] - 1][a[1] + 1][1] == 0)
            rot++;
        if (nine_1[5][2] == 1 && matrix[a[0]][a[1] + 1][1] == 0)
            rot++;
        if (nine_1[2][2] == 1 && matrix[a[0] + 1][a[1] + 1][1] == 0)
            rot++;
        if (nine_1[4][2] == 1 && nine_1[4][3] == 1)
            rot++;

        if (rot == 4)
        {
            goto here1;
        }
        else
        {
            matrixequa(matrix_t, matrix);
            break;
        }
    here1:

        for (int i = 0; i < 4; i++)
        {
            if (nine_1[6][2] == 1)
                matrix[a[0] - 1][a[1] - 1][i] = nine_1[6][i];
            if (nine_1[3][2] == 1)
                matrix[a[0]][a[1] - 1][i] = nine_1[3][i];
            if (nine_1[0][2] == 1)
                matrix[a[0] + 1][a[1] - 1][i] = nine_1[0][i];
            if (nine_1[7][2] == 1)
                matrix[a[0] - 1][a[1]][i] = nine_1[7][i];

            matrix[a[0]][a[1]][i] = nine_1[4][i];

            if (nine_1[1][2] == 1)
                matrix[a[0] + 1][a[1]][i] = nine_1[1][i];
            if (nine_1[8][2] == 1)
                matrix[a[0] - 1][a[1] + 1][i] = nine_1[8][i];
            if (nine_1[5][2] == 1)
                matrix[a[0]][a[1] + 1][i] = nine_1[5][i];
            if (nine_1[2][2] == 1)
                matrix[a[0] + 1][a[1] + 1][i] = nine_1[2][i];
        }
        matrixequa(matrix, matrix_t);

        break;
    case 120:
        if (nine_1[2][2] == 1 && matrix[a[0] - 1][a[1] - 1][1] == 0)
            rot++;
        if (nine_1[5][2] == 1 && matrix[a[0]][a[1] - 1][1] == 0)
            rot++;
        if (nine_1[8][2] == 1 && matrix[a[0] + 1][a[1] - 1][1] == 0)
            rot++;
        if (nine_1[1][2] == 1 && matrix[a[0] - 1][a[1]][1] == 0)
            rot++;
        if (nine_1[7][2] == 1 && matrix[a[0] + 1][a[1]][1] == 0)
            rot++;
        if (nine_1[0][2] == 1 && matrix[a[0] - 1][a[1] + 1][1] == 0)
            rot++;
        if (nine_1[3][2] == 1 && matrix[a[0]][a[1] + 1][1] == 0)
            rot++;
        if (nine_1[6][2] == 1 && matrix[a[0] + 1][a[1] + 1][1] == 0)
            rot++;
        if (nine_1[4][2] == 1 && nine_1[4][3] == 1)
            rot++;
        if (rot == 4)
        {
            goto here2;
        }
        else
        {
            matrixequa(matrix_t, matrix);
            break;
        }
    here2:
        for (int i = 0; i < 4; i++)
        {
            if (nine_1[2][2] == 1)
                matrix[a[0] - 1][a[1] - 1][i] = nine_1[2][i];
            if (nine_1[5][2] == 1)
                matrix[a[0]][a[1] - 1][i] = nine_1[5][i];
            if (nine_1[8][2] == 1)
                matrix[a[0] + 1][a[1] - 1][i] = nine_1[8][i];
            if (nine_1[1][2] == 1)
                matrix[a[0] - 1][a[1]][i] = nine_1[1][i];

            matrix[a[0]][a[1]][i] = nine_1[4][i];

            if (nine_1[7][2] == 1)
                matrix[a[0] + 1][a[1]][i] = nine_1[7][i];
            if (nine_1[0][2] == 1)
                matrix[a[0] - 1][a[1] + 1][i] = nine_1[0][i];
            if (nine_1[3][2] == 1)
                matrix[a[0]][a[1] + 1][i] = nine_1[3][i];
            if (nine_1[6][2] == 1)
                matrix[a[0] + 1][a[1] + 1][i] = nine_1[6][i];
        }

        break;
        matrixequa(matrix, matrix_t);
    }

    if (blocktype == 1)
    {
        I_rotation(matrix, matrix_t, mode);
        goto here;
    }
    else
    {
        goto here;
    }

here:
    return 0;
}
int search_r(int matrix[12][22][4], int coordinate[2])
{
    int re = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][3] == 1)
            {
                coordinate[0] = j;
                coordinate[1] = i;
                re = 1;
                if (re == 1)
                {
                    goto here;
                }
            }
        }
    }
here:
    return re;
}
int recode5block(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2])
{

    int var = recode4block(matrix, recodedblock_1);
    search_r(matrix, kernel);
    return (var + matrix[kernel[0]][kernel[1]][3]);
}
int inputselection(int key)
{
    int re = 0;
    if (key == 75 || key == 77 || key == 80 || key == 122)
    {
        re = 1;
    }
    else if (key == 72 || key == 120)
    {
        re = 2;
    }
    else
    {
        re = 0;
    }

    return re;
}
int search_I(int matrix[12][22][4], int coordinate[4])
{
    int re = 0;
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][3] == 1)
            {
                if (re >= 2)
                {
                    goto here;
                }
                coordinate[2 * re] = j;
                coordinate[2 * re + 1] = i;
                re++;
            }
        }
    }
here:
    return re;
}
int I_rotation(int matrix[12][22][4], int matrix_t[12][22][4], int mode)
{
    int a[4];
    int b[2] = {0};
    search_I(matrix, a);
    b[0] = a[0] - a[2];
    b[1] = a[2] - a[3];
    if (b[0] != 0)
    {

        for (int i = 0; i < 4; i++)
        {
            matrix[a[0]][a[1]][i] = 0;
            matrix[a[0] + 1][a[1]][i] = 0;
            matrix[a[0] + 3][a[1]][i] = 0;
        }
        matrix[a[0] + 2][a[1] - 1][0] = 3;
        matrix[a[0] + 2][a[1] + 1][0] = 3;
        matrix[a[0] + 2][a[1] + 2][0] = 3;

        matrix[a[0] + 2][a[1] - 1][1] = 1;
        matrix[a[0] + 2][a[1] + 1][1] = 1;
        matrix[a[0] + 2][a[1] + 2][1] = 1;

        matrix[a[0] + 2][a[1] - 1][2] = 1;
        matrix[a[0] + 2][a[1] + 1][2] = 1;
        matrix[a[0] + 2][a[1] + 2][2] = 1;

        matrix[a[0] + 2][a[1] - 1][3] = 1;
        matrix[a[0] + 2][a[1] + 2][3] = 1;
        matrixequa(matrix, matrix_t);
    }

    return 0;
}
int movingcase80(int matrix[12][22][4], int matrix_t[12][22][4])
{
    int c = 0;
    int matrix2[12][22][4] = {0};
    int recodedblock_1[4][6] = {0};
    int recodedblock_2[4][6] = {0};
    int kernel[2] = {0};
    int kernel2[2] = {0};
    matrixequa(matrix, matrix2);
    if (recode5block(matrix, recodedblock_2, kernel2) == 0) // if we cant find any block which can be moved

    {
        goto here;
    }

    blolckmoving(matrix_t, 80);
    recode5block(matrix_t, recodedblock_1, kernel);
    movingblockerasing(matrix2);
    if (newspace_check(matrix2, recodedblock_1) == 1) // if any collision exist
    {

        unmovable(matrix, recodedblock_2);
        matrixequa(matrix, matrix_t);
        goto here;
    }
    else
    {

        blolckmoving(matrix, 80);
        matrixequa(matrix, matrix_t);
        c = 1;
        goto here;
    }
here:
    return c;
}
int movingcase77(int matrix[12][22][4], int matrix_t[12][22][4])
{
    int c = 0;
    int matrix2[12][22][4] = {0};
    matrixequa(matrix, matrix2);
    int recodedblock_1[4][6] = {0};
    int recodedblock_2[4][6] = {0};
    int kernel[2] = {0};
    int kernel2[2] = {0};
    if (recode5block(matrix, recodedblock_2, kernel2) == 0) // if we cant find any block which can be moved

    {
        goto here;
    }

    blolckmoving(matrix_t, 77);
    recode5block(matrix_t, recodedblock_1, kernel);
    movingblockerasing(matrix2);
    if (newspace_check(matrix2, recodedblock_1) == 1) // if any collision exist
    {

        matrixequa(matrix, matrix_t);

        goto here;
    }
    else
    {

        blolckmoving(matrix, 77);
        matrixequa(matrix, matrix_t);
        c = 1;
        goto here;
    }
here:
    return c;
}
int movingcase75(int matrix[12][22][4], int matrix_t[12][22][4])
{
    int c = 0;
    int matrix2[12][22][4] = {0};
    matrixequa(matrix, matrix2);
    int recodedblock_1[4][6] = {0};
    int recodedblock_2[4][6] = {0};
    int kernel[2] = {0};
    int kernel2[2] = {0};
    if (recode5block(matrix, recodedblock_2, kernel2) == 0) // if we cant find any block which can be moved

    {
        goto here;
    }

    blolckmoving(matrix_t, 75);
    recode5block(matrix_t, recodedblock_1, kernel);
    movingblockerasing(matrix2);
    if (newspace_check(matrix2, recodedblock_1) == 1) // if any collision exist
    {

        matrixequa(matrix, matrix_t);

        goto here;
    }
    else
    {

        blolckmoving(matrix, 75);
        matrixequa(matrix, matrix_t);
        c = 1;
        goto here;
    }
here:
    return c;
}
