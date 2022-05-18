#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<thread>

using namespace std;

void resizeConsole(int width, int height); // thay doi kich thuoc man hinh console giu scrollbar

void ClearConsole(); // xoa man hinh console

void gotoXY(int x, int y); // di chuyen den vi tri x, y tren man hinh console

void textColor(int x); // to mau

void showScrollBar(bool show); // an/hien srcollbar

//void setScreenBufferSize(SHORT width, SHORT height); // xet screen buffer size

void disableResizeConsole();

void WriteBlockChar(char * Arraych, int row, int col, int x, int y, int color);

//xay dung ham  tim nguyen am co tan so xuat hien nhieu nhat
char find_vowelMax(string s);

// kiem tra xem 1 tu co chua ky tu (khong co index)
int ktra_1(string s, char a);

int ktra_2(string s1, string s2);

//tim cac tu trong brain bot co chua cac tu bot_choose_right
string find_botRight(vector<string> v, string s);

//tim cac tu trong brain bot khong chua cac tu bot_chooose_wrong
string find_botWrong(vector<string> v, string s);

// tim ky tu xh nhieu nhat
char find_max(map<char, int> m, string s);
