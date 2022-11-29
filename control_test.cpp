#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

void SetColor(int f=7,int b=0)//a fumction in windows.h can change font color
{
 unsigned short ForeColor=f+16*b;
 HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(hCon,ForeColor);
}

int main(){
system("chcp 65001");
system("cls");
int ran;
for(int i=0;i<30;i++){
ran =rand()%7;
cout<<ran;
}


}