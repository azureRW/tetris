#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
int main(){
    int c1=0;

    for(;1;){
    c1=getch();
    if(c1==224){
        c1=getch();
    }
    cout<<c1<<"\n";
    }
}