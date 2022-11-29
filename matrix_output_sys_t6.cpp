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
void set7blocks(int matrix[12][22][4], int i); // 4:circle; 3:long; 14:凸; 5:znti Z; 6:Z; 2:L; 1:anti L;
void blocks_collision_test(int matrix[12][22][4], int matrix_t[12][22][4], int checking_instruction);
int recode4block(int matrix[12][22][4], int recodedblock_1[4][6]);
int recode5block(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2]);
void matrixequa(int matrix[12][22][4], int matrix_t[12][22][4]); // let latter matrix equal to former
int newspace_check(int matrix[12][22][4], int recodedblock_1[4][6]);
void unmovable(int matrix[12][22][4], int recodedblock_1[4][6]);
int movingblockerasing(int matrix[12][22][4]);
void putback(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2]);
void matrix_contemt_opt(int matrix[12][22][4], int k);
int block_rotation(int matrix[12][22][4], int matrix_t[12][22][4], int mode, int bloclktype); // mode: 72 for clockwise , 120 for counterclockwise
int search_r(int matrix[12][22][4], int coordinate[2]);
int inputselection(int key);
int main()
{
    int matrix[12][22][4] = {0};
    int matrix_t[12][22][4] = {0};
    int recodedblock_1[4][6] = {0}; // {block x axis,block y axis,z1,z2,z3}
    int recodedblock_3[4][6] = {0};
    int kernel2[2] = {0};
    system("chcp 65001");
    system("cls");

    set_background(matrix_t);
    set_background(matrix); // the instruction makes the main matrix print the frame of game
    //*matrix_output(matrix); //the instruction print matrix on cmd
    // the form of the input matrix is a [12][22][2] matrix [12] for x [22] for y [2] will be the characteristics of the blocks
    //*set7blocks(matrix, 1);

    set7blocks(matrix_t, 1);
    set7blocks(matrix, 1);
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
            break;
        case 2:
            block_rotation(matrix, matrix_t, key, 1);
            matrix_output(matrix);
            break;
        }

        if (recode5block(matrix, recodedblock_3, kernel2) == 0)
        {
            set7blocks(matrix_t, 14);
            set7blocks(matrix, 14);
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
    search_r(matrix, a);
    matrix[a[0]][a[1]][3] = 0;
    matrix[a[0]][a[1] + 1][3] = 1;

there:
    return 0;
}
int moving_right_test(int matrix[12][22][4])
{
    int a[2] = {0};
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
    search_r(matrix, a);
    matrix[a[0]][a[1]][3] = 0;
    matrix[a[0] + 1][a[1]][3] = 1;
there:
    return 0;
}
int moving_left_test(int matrix[12][22][4])
{
    int a[2] = {0};
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
    search_r(matrix, a);
    matrix[a[0]][a[1]][3] = 0;
    matrix[a[0] - 1][a[1]][3] = 1;
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
void set7blocks(int matrix[12][22][4], int i)
{
    switch (i)
    {
    case 4: // red circle
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
        break;
    case 3: // blue long
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

        matrix[6][1][3] = 1;

        break;
    case 14: // yellow(凸)
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
        break;
    case 5: // purple anti Z
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
        break;
    case 6: // shit Z
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
        break;
    case 2: // green L
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
        break;
    case 1: // darkblue anti L
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
        break;
    }
}
void blocks_collision_test(int matrix[12][22][4], int matrix_t[12][22][4], int checking_instruction)
{
    int recodedblock_1[4][6] = {0};
    int recodedblock_2[4][6] = {0};
    int jumpflag = 0;
    int kernel[2] = {0};
    int kernel2[2] = {0};
    switch (checking_instruction) // instruction=key_name
    {

    case 80:

    here:
        if (recode5block(matrix, recodedblock_2, kernel2) == 0) // if we cant find any block which can be moved
        {
            break;
        }

        blolckmoving(matrix_t, 80);
        recode5block(matrix_t, recodedblock_1, kernel);
        movingblockerasing(matrix);
        if (newspace_check(matrix, recodedblock_1) == 1) // if any collision exist
        {

            putback(matrix, recodedblock_2, kernel2);
            unmovable(matrix, recodedblock_2);
            matrixequa(matrix, matrix_t);
            break;
        }
        else
        {
            putback(matrix, recodedblock_1, kernel);
            matrixequa(matrix, matrix_t);
            if (jumpflag > 0)
            {
                jumpflag--;
                goto there;
            }
            break;
        }
    case 122:
        jumpflag = 19;
    there:
        goto here;
        break;
    case 75:

        if (recode5block(matrix, recodedblock_2, kernel2) == 0)
        {
            break;
        }
        blolckmoving(matrix_t, 75);
        recode5block(matrix_t, recodedblock_1, kernel);
        movingblockerasing(matrix);
        if (newspace_check(matrix, recodedblock_1) == 1)
        {

            putback(matrix, recodedblock_2, kernel2);
            matrixequa(matrix, matrix_t);
            break;
        }
        else
        {
            putback(matrix, recodedblock_1, kernel);
            matrixequa(matrix, matrix_t);
            break;
        }
    case 77:

        if (recode5block(matrix, recodedblock_2, kernel2) == 0)
        {
            break;
        }
        blolckmoving(matrix_t, 77);
        recode5block(matrix_t, recodedblock_1, kernel);
        movingblockerasing(matrix);
        if (newspace_check(matrix, recodedblock_1) == 1)
        {

            putback(matrix, recodedblock_2, kernel2);
            matrixequa(matrix, matrix_t);
            break;
        }
        else
        {
            putback(matrix, recodedblock_1, kernel);
            matrixequa(matrix, matrix_t);
            break;
        }
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
        recodedblock_1[i][4] = z[2];
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
    search_r(matrix, a);
    matrix[a[0]][a[1]][3] = 0;
}
int movingblockerasing(int matrix[12][22][4])
{
    int block_num = 0;
    int x[4] = {0};
    int y[4] = {0};
    int z[4] = {0};
    int a[2] = {0};
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (matrix[j][i][2] == 1)
            {

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

here:
    search_r(matrix, a);
    matrix[a[0]][a[1]][3] = 0;
    return 0;
}
void putback(int matrix[12][22][4], int recodedblock_1[4][6], int kernel[2])
{
    for (int i = 0; i < 4; i++)
    {
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][0] = recodedblock_1[i][2];
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][1] = recodedblock_1[i][3];
        matrix[recodedblock_1[i][0]][recodedblock_1[i][1]][2] = recodedblock_1[i][4];
    }
    matrix[kernel[0]][kernel[1]][3] = 1;
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
int block_rotation(int matrix[12][22][4], int matrix_t[12][22][4], int mode, int bloclktype)
{

    int a[2] = {0};
    int a2[2] = {0}; // in this function kernel is a
    int nine_1[9][4] = {0};
    int rot = 0;
    int kernel[2]={0};
    int b[4][6];//recodedblock
    if (bloclktype != 4 && bloclktype != 3)
    {
        int recodedblock_1[4][6];
        int recodedblock_2[4][6];
        search_r(matrix, a);
        if (a[1] == 1)
        {
            recode5block(matrix, recodedblock_2, a2);
            blolckmoving(matrix_t, 80);
            recode5block(matrix_t, recodedblock_1, a);
            movingblockerasing(matrix);
            if (newspace_check(matrix, recodedblock_1) == 1)
            {   


                putback(matrix, recodedblock_2, a);
                matrixequa(matrix, matrix_t);
            }
            else
            {
                putback(matrix, recodedblock_1, a);
                matrixequa(matrix, matrix_t);
            }
        }
        if (a[0] == 1)
        {
            recode5block(matrix, recodedblock_2, a2);
            blolckmoving(matrix_t, 77);
            recode5block(matrix_t, recodedblock_1, a);
            movingblockerasing(matrix);
            if (newspace_check(matrix, recodedblock_1) == 1)
            {

                putback(matrix, recodedblock_2, a);
                matrixequa(matrix, matrix_t);
            }
            else
            {
                putback(matrix, recodedblock_1, a);
                matrixequa(matrix, matrix_t);
            }
        }
        if (a[0] == 10)
        {
            recode5block(matrix, recodedblock_2, a2);
            blolckmoving(matrix_t, 75);
            recode5block(matrix_t, recodedblock_1, a);
            movingblockerasing(matrix);
            if (newspace_check(matrix, recodedblock_1) == 1)
            {

                putback(matrix, recodedblock_2, a);
                matrixequa(matrix, matrix_t);
            }
            else
            {
                putback(matrix, recodedblock_1, a);
                matrixequa(matrix, matrix_t);
            }
        }
        if (a[1] == 20)
        {
            goto here;
        }
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
        recode5block(matrix,b,kernel);
        movingblockerasing(matrix);
    }
    else{
    goto here;
    }
    switch (mode)
    {
    case 72:
    if(nine_1[6][2] == 1&&matrix[a[0] - 1][a[1] - 1][1]==0)
        rot++;
    if(nine_1[3][2] == 1&&matrix[a[0]][a[1] - 1][1]==0)
        rot++;
    if(nine_1[0][2] == 1&&matrix[a[0] + 1][a[1] - 1][1]==0)
        rot++;
    if(nine_1[7][2] == 1&&matrix[a[0]-1][a[1] ][1]==0)
        rot++;
    if(nine_1[1][2] == 1&&matrix[a[0] + 1][a[1] ][1]==0)
        rot++;
    if(nine_1[8][2] == 1&&matrix[a[0]-1][a[1] + 1][1]==0)
        rot++;
    if(nine_1[5][2] == 1&&matrix[a[0] ][a[1] + 1][1]==0)
        rot++;
    if(nine_1[2][2] == 1&&matrix[a[0]+1][a[1] + 1][1]==0)
        rot++;
    if(nine_1[4][2]==1&&nine_1[4][1]==1)
        rot++;

    if (rot==4){
        goto here1;
    }
    else{
        putback(matrix,b,kernel);
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
    if(nine_1[2][2] == 1&&matrix[a[0] - 1][a[1] - 1][1]==0)
        rot++;
    if(nine_1[5][2] == 1&&matrix[a[0]][a[1] - 1][1]==0)
        rot++;
    if(nine_1[8][2] == 1&&matrix[a[0] + 1][a[1] - 1][1]==0)
        rot++;
    if(nine_1[1][2] == 1&&matrix[a[0]-1][a[1] ][1]==0)
        rot++;
    if(nine_1[7][2] == 1&&matrix[a[0] + 1][a[1] ][1]==0)
        rot++;
    if(nine_1[0][2] == 1&&matrix[a[0]-1][a[1] + 1][1]==0)
        rot++;
    if(nine_1[3][2] == 1&&matrix[a[0] ][a[1] + 1][1]==0)
        rot++;
    if(nine_1[6][2] == 1&&matrix[a[0]+1][a[1] + 1][1]==0)
        rot++;
    if(nine_1[4][2]==1&&nine_1[4][1]==1)
        rot++;
    if (rot==4){
        goto here2;
    }
    else{
        putback(matrix,b,kernel);
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
            }
        }
    }
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
