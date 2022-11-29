#include<iostream>
#include<windows.h>
using namespace std;

void SetColor(int f=7,int b=0)//a fumction in windows.h can change font color
{
 unsigned short ForeColor=f+16*b;
 HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(hCon,ForeColor);
}

int main(){

int i=0;
system("chcp 65001");
system("cls");
for(int i=0;i<12;i++)
{
    cout<<"██";
}
cout<<"\n";
for(int i=0;i<20;i++){
    cout<<"██                    ██"<<"\n";
}
for(int i=0;i<12;i++)
{
    cout<<"██";
}
system("pause");
return 0;
}
